// Copyright (c) 2025 Arek.Wered;


#include "InteractComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enums.h"
#include "InteractInterface.h"
#include "InputAction.h"
#include "InputMappingContext.h"


UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/AW_InteractionSystem/Input/IMC_Interact.IMC_Interact"));
	if (MappingContextFinder.Succeeded())
	{
		InteractMappingContext = MappingContextFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> PressActionFinder(TEXT("/AW_InteractionSystem/Input/Actions/IA_Interact_Press.IA_Interact_Press"));
	if (PressActionFinder.Succeeded())
	{
		InteractPressAction = PressActionFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> HoldActionFinder(TEXT("/AW_InteractionSystem/Input/Actions/IA_Interact_Hold.IA_Interact_Hold"));
	if (HoldActionFinder.Succeeded())
	{
		InteractHoldAction = HoldActionFinder.Object;
	}
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	PawnOwner = GetOwner<APawn>();
	PlayerController = PawnOwner->GetController<APlayerController>();

	UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())};
	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(PlayerController->InputComponent)};

	Subsystem->AddMappingContext(InteractMappingContext, 0);

	EnhancedInputComponent->BindAction(InteractPressAction, ETriggerEvent::Started, this, &UInteractComponent::InteractPressStarted);
	EnhancedInputComponent->BindAction(InteractPressAction, ETriggerEvent::Triggered, this, &UInteractComponent::InteractPressTriggered);
	EnhancedInputComponent->BindAction(InteractPressAction, ETriggerEvent::Completed, this, &UInteractComponent::InteractPressCompleted);

	EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Started, this, &UInteractComponent::InteractHoldStarted);
	EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Ongoing, this, &UInteractComponent::InteractHoldOngoing);
	EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Canceled, this, &UInteractComponent::InteractHoldCanceled);
	EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Triggered, this, &UInteractComponent::InteractHoldTriggered);
	EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Completed, this, &UInteractComponent::InteractHoldCompleted);
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformInteractionCheck();
}

void UInteractComponent::PerformInteractionCheck()
{
	if (!bCanCheckInteraction)
	{
		return;
	}

	// Get camera location and direction
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Define the start and end points of the line trace
	const FVector Start{CameraLocation};
	const FVector End{Start + CameraRotation.Vector() * InteractionDistance};

	// Perform the line trace
	FHitResult HitResult;
	const bool bHit
	{
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility
		)
	};

	/**
	 * Clear interaction if at least one of below conditions is met:
	 * - nothing was hit
	 * - HitResult is not an actor
	 * - HitActor does not implement interact interface
	 * - HitActor is not allowed to interact
	 */
	AActor* HitActor{HitResult.GetActor()};
	UPrimitiveComponent* HitComponent{HitResult.GetComponent()};
	if (!bHit ||
		!HitActor ||
		!HitActor->Implements<UInteractInterface>() ||
		!IInteractInterface::Execute_GetCanInteract(HitActor))
	{
		ClearInteraction();
		return;
	}

	// Check if a custom interaction area is used
	const bool bUsesCustomInteractArea{IInteractInterface::Execute_DoesUseCustomInteractArea(HitActor)};

	// Early return if hits the same Actor
	// If using a custom interaction area, compare components
	if (bUsesCustomInteractArea && HitComponent == InteractableHitComponent)
	{
		return;
	}
	// If not using a custom interaction area, compare actors
	if (!bUsesCustomInteractArea && HitActor == InteractableActor)
	{
		return;
	}

	// Hide UI from a previously focused interactable actor
	if (InteractableActor)
	{
		IInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
	}

	// Depending on custom area usage, set or clear interaction
	if (bUsesCustomInteractArea)
	{
		if (HitComponent->GetCollisionProfileName() == FName("InteractArea"))
		{
			SetInteraction(HitActor, HitComponent);
		}
		else
		{
			ClearInteraction();
		}
	}
	else
	{
		SetInteraction(HitActor, HitComponent);
	}
}

void UInteractComponent::SetInteraction(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent)
{
	IInteractInterface::Execute_DisplayInteractionUI(InteractedActor, true);
	InteractableActor = InteractedActor;
	InteractableHitComponent = InteractedComponent;
}

void UInteractComponent::ClearInteraction()
{
	if (bIsHolding)
	{
		InteractHoldCanceled();
	}

	if (InteractableActor)
	{
		IInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
		InteractableActor = nullptr;
		InteractableHitComponent = nullptr;
	}
}

void UInteractComponent::InteractPressStarted()
{
	if (InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Press)
	{
		IInteractInterface::Execute_InteractPressStarted(InteractableActor, PawnOwner);
	}
}

void UInteractComponent::InteractPressTriggered()
{
	if (InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Press)
	{
		IInteractInterface::Execute_InteractPressTriggered(InteractableActor);
	}
}

void UInteractComponent::InteractPressCompleted()
{
	if (InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Press)
	{
		IInteractInterface::Execute_InteractPressCompleted(InteractableActor);
	}
}

void UInteractComponent::InteractHoldStarted(const FInputActionInstance& Instance)
{
	if (!InteractableActor || !InteractableActor->Implements<UInteractInterface>() || IInteractInterface::Execute_GetInteractType(InteractableActor) != EInteractType::Hold)
	{
		return;
	}

	for (UInputTrigger* Trigger : Instance.GetTriggers())
	{
		if (UInputTriggerHold* TriggerHold{Cast<UInputTriggerHold>(Trigger)})
		{
			TriggerHold->HoldTimeThreshold = IInteractInterface::Execute_InteractHoldStarted(InteractableActor, PawnOwner);
			break;
		}
	}

	bIsHolding = true;
}

void UInteractComponent::InteractHoldOngoing(const FInputActionInstance& Instance)
{
	if (bIsHolding && InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Hold)
	{
		IInteractInterface::Execute_InteractHoldOngoing(InteractableActor, Instance.GetElapsedTime());
	}
}

void UInteractComponent::InteractHoldCanceled()
{
	if (bIsHolding && InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Hold)
	{
		bIsHolding = false;

		IInteractInterface::Execute_InteractHoldCanceled(InteractableActor);
	}
}

void UInteractComponent::InteractHoldTriggered()
{
	if (bIsHolding && InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Hold)
	{
		IInteractInterface::Execute_InteractHoldTriggered(InteractableActor);
	}
}

void UInteractComponent::InteractHoldCompleted()
{
	if (bIsHolding && InteractableActor && InteractableActor->Implements<UInteractInterface>() && IInteractInterface::Execute_GetInteractType(InteractableActor) == EInteractType::Hold)
	{
		bIsHolding = false;

		IInteractInterface::Execute_InteractHoldCompleted(InteractableActor);
	}
}
