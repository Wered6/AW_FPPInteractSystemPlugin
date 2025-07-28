// Copyright (c) 2025 Arek.Wered;


#include "BaseClasses/InteractableActorBase.h"
#include "InteractableComponent.h"


AInteractableActorBase::AInteractableActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
}

void AInteractableActorBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
	InteractableComponent->DisplayInteractionUI(bShowInteract);
}

void AInteractableActorBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractableComponent->InteractPressStarted(OtherInstigator);
}

void AInteractableActorBase::InteractPressTriggered_Implementation()
{
	InteractableComponent->InteractPressTriggered();
}

void AInteractableActorBase::InteractPressCompleted_Implementation()
{
	InteractableComponent->InteractPressCompleted();
}

float AInteractableActorBase::InteractHoldStarted_Implementation(AActor* OtherInstigator)
{
	return InteractableComponent->InteractHoldStarted(OtherInstigator);
}

void AInteractableActorBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
	InteractableComponent->InteractHoldOngoing(ElapsedSeconds);
}

void AInteractableActorBase::InteractHoldTriggered_Implementation()
{
	InteractableComponent->InteractHoldTriggered();
}

void AInteractableActorBase::InteractHoldCanceled_Implementation()
{
	InteractableComponent->InteractHoldCanceled();
}

void AInteractableActorBase::InteractHoldCompleted_Implementation()
{
	InteractableComponent->InteractHoldCompleted();
}

bool AInteractableActorBase::DoesUseCustomInteractArea_Implementation()
{
	return InteractableComponent->DoesUseCustomInteractArea();
}

void AInteractableActorBase::SetCanInteract_Implementation(const bool bNewCanInteract)
{
	InteractableComponent->SetCanInteract(bNewCanInteract);
}

bool AInteractableActorBase::GetCanInteract_Implementation()
{
	return InteractableComponent->GetCanInteract();
}

EInteractType AInteractableActorBase::GetInteractType_Implementation()
{
	return InteractableComponent->GetInteractType();
}
