// Copyright (c) 2025 Arek.Wered;


#include "InteractableComponent.h"
#include "InteractIconWidget.h"
#include "InteractInterface.h"
#include "BaseClasses/InteractableActorBase.h"
#include "BaseClasses/InteractableCharacterBase.h"
#include "BaseClasses/InteractablePawnBase.h"
#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY_CLASS(UInteractableComponent, LogInteractableComponent);

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UInteractIconWidget> InteractIconWidgetClassFinder(TEXT("/AW_InteractionSystem/WBP_InteractIcon"));
	if (InteractIconWidgetClassFinder.Succeeded())
	{
		InteractIconWidgetClass = InteractIconWidgetClassFinder.Class;
	}
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeInteractWidget();
	UpdateWidgetAttachment();
}

void UInteractableComponent::OnRegister()
{
	Super::OnRegister();

	if (!ActorOwner.IsValid())
	{
		ActorOwner = GetOwner();
	}

	UClass* InteractableActorBaseClass{AInteractableActorBase::StaticClass()};
	UClass* InteractablePawnBaseClass{AInteractablePawnBase::StaticClass()};
	UClass* InteractableCharacterBaseClass{AInteractableCharacterBase::StaticClass()};

	const bool bIsOwnerACorrectClass
	{
		ActorOwner->IsA(InteractableActorBaseClass) ||
		ActorOwner->IsA(InteractablePawnBaseClass) ||
		ActorOwner->IsA(InteractableCharacterBaseClass)
	};
	if (!bIsOwnerACorrectClass)
	{
		UE_LOG(LogInteractableComponent,
		       Error,
		       TEXT("%s owned by %s. Component must be owned by a %s, %s or %s"),
		       *GetName(),
		       *GetNameSafe(ActorOwner.Get()),
		       *InteractableActorBaseClass->GetName(),
		       *InteractablePawnBaseClass->GetName(),
		       *InteractableCharacterBaseClass->GetName()
		)
	}
}

void UInteractableComponent::AddOutlineMeshComponent(UMeshComponent* MeshComponent)
{
	OutlineMeshComponents.Add(MeshComponent);
}

void UInteractableComponent::SetOutlineMeshComponents(const TArray<UMeshComponent*>& NewOutlineMeshComponents)
{
	OutlineMeshComponents = NewOutlineMeshComponents;
}

void UInteractableComponent::InitializeInteractWidget()
{
	InteractIconWidget = CreateWidget<UInteractIconWidget>(GetWorld(), InteractIconWidgetClass);
	InteractIconWidgetComponent = NewObject<UWidgetComponent>(this, TEXT("Interact Icon Widget Component"));

	InteractIconWidget->Init(InteractType,
	                         MinIconOpacity,
	                         IconSize,
	                         MinProgressCircleOpacity,
	                         ProgressCircleSize);

	InteractIconWidget->SetVisibility(ESlateVisibility::Hidden);
	InteractIconWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractIconWidgetComponent->SetDrawAtDesiredSize(true);
	InteractIconWidgetComponent->SetWidget(InteractIconWidget);
	InteractIconWidgetComponent->RegisterComponent();
}

void UInteractableComponent::UpdateWidgetAttachment() const
{
	AActor* ActorOwnerDeref{ActorOwner.Get()};
	USceneComponent* WidgetAttachComponent{IInteractInterface::Execute_GetWidgetAttachmentComponent(ActorOwnerDeref)};

	if (!WidgetAttachComponent)
	{
		WidgetAttachComponent = ActorOwnerDeref->GetRootComponent();
	}

	InteractIconWidgetComponent->AttachToComponent(WidgetAttachComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void UInteractableComponent::UpdateOutline(const bool bHighlight)
{
	for (UMeshComponent* OutlineMeshComponent : OutlineMeshComponents)
	{
		if (OutlineMeshComponent)
		{
			OutlineMeshComponent->SetRenderCustomDepth(bHighlight);
			OutlineMeshComponent->SetCustomDepthStencilValue(bHighlight ? 1 : 0);
		}
	}
}

void UInteractableComponent::DisplayInteractionUI(const bool bShowInteract)
{
	InteractIconWidget->SetVisibility(bShowInteract ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	UpdateOutline(bShowInteract);
}

void UInteractableComponent::InteractPressStarted(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
	UE_LOG(LogTemp, Log, TEXT("PressStarted"))
}

void UInteractableComponent::InteractPressTriggered()
{
	UE_LOG(LogTemp, Log, TEXT("PressTriggered"));
}

void UInteractableComponent::InteractPressCompleted()
{
	InteractInstigator = nullptr;
	UE_LOG(LogTemp, Log, TEXT("PressCompleted"));
}

float UInteractableComponent::InteractHoldStarted(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
	UE_LOG(LogTemp, Log, TEXT("HoldStarted"));

	return HoldTimeThreshold;
}

void UInteractableComponent::InteractHoldOngoing(const float ElapsedSeconds)
{
	constexpr float MinClampProgressFraction{0.f};
	constexpr float MaxClampProgressFraction{1.f};
	const float ProgressFraction{FMath::Clamp(ElapsedSeconds / HoldTimeThreshold, MinClampProgressFraction, MaxClampProgressFraction)};

	InteractIconWidget->SetIconOpacity(ProgressFraction);
	InteractIconWidget->SetProgressCircleOpacity(ProgressFraction);
	InteractIconWidget->SetProgressCirclePercent(ProgressFraction);
}

void UInteractableComponent::InteractHoldTriggered()
{
	UE_LOG(LogTemp, Log, TEXT("InteractHoldTriggered"));
}

void UInteractableComponent::InteractHoldCanceled()
{
	InteractInstigator = nullptr;
	InteractIconWidget->SetProgressCircleOpacity(0.f);
	InteractIconWidget->SetProgressCirclePercent(0.f);
	InteractIconWidget->SetIconOpacity(0.f);

	UE_LOG(LogTemp, Log, TEXT("HoldCanceled"));
}

void UInteractableComponent::InteractHoldCompleted()
{
	InteractInstigator = nullptr;

	UE_LOG(LogTemp, Log, TEXT("HoldCompleted"));
}

bool UInteractableComponent::DoesUseCustomInteractArea() const
{
	return bUseCustomInteractArea;
}

void UInteractableComponent::SetCanInteract(const bool bNewCanInteract)
{
	bCanInteract = bNewCanInteract;
}

bool UInteractableComponent::GetCanInteract() const
{
	return bCanInteract;
}

EInteractType UInteractableComponent::GetInteractType() const
{
	return InteractType;
}
