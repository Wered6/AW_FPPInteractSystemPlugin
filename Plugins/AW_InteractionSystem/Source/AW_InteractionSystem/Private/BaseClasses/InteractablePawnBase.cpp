// Copyright (c) 2025 Arek.Wered;


#include "BaseClasses/InteractablePawnBase.h"
#include "InteractableComponent.h"


AInteractablePawnBase::AInteractablePawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
}

void AInteractablePawnBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
	InteractableComponent->DisplayInteractionUI(bShowInteract);
}

void AInteractablePawnBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractableComponent->InteractPressStarted(OtherInstigator);
}

void AInteractablePawnBase::InteractPressTriggered_Implementation()
{
	InteractableComponent->InteractPressTriggered();
}

void AInteractablePawnBase::InteractPressCompleted_Implementation()
{
	InteractableComponent->InteractPressCompleted();
}

float AInteractablePawnBase::InteractHoldStarted_Implementation(AActor* OtherInstigator)
{
	return InteractableComponent->InteractHoldStarted(OtherInstigator);
}

void AInteractablePawnBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
	InteractableComponent->InteractHoldOngoing(ElapsedSeconds);
}

void AInteractablePawnBase::InteractHoldTriggered_Implementation()
{
	InteractableComponent->InteractHoldTriggered();
}

void AInteractablePawnBase::InteractHoldCanceled_Implementation()
{
	InteractableComponent->InteractHoldCanceled();
}

void AInteractablePawnBase::InteractHoldCompleted_Implementation()
{
	InteractableComponent->InteractHoldCompleted();
}

bool AInteractablePawnBase::DoesUseCustomInteractArea_Implementation()
{
	return InteractableComponent->DoesUseCustomInteractArea();
}

void AInteractablePawnBase::SetCanInteract_Implementation(const bool bNewCanInteract)
{
	InteractableComponent->SetCanInteract(bNewCanInteract);
}

bool AInteractablePawnBase::GetCanInteract_Implementation()
{
	return InteractableComponent->GetCanInteract();
}

EInteractType AInteractablePawnBase::GetInteractType_Implementation()
{
	return InteractableComponent->GetInteractType();
}
