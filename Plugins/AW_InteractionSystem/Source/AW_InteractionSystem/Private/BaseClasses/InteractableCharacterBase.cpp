// Copyright (c) 2025 Arek.Wered;


#include "BaseClasses/InteractableCharacterBase.h"
#include "InteractableComponent.h"


AInteractableCharacterBase::AInteractableCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
}

void AInteractableCharacterBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
	InteractableComponent->DisplayInteractionUI(bShowInteract);
}

void AInteractableCharacterBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractableComponent->InteractPressStarted(OtherInstigator);
}

void AInteractableCharacterBase::InteractPressTriggered_Implementation()
{
	InteractableComponent->InteractPressTriggered();
}

void AInteractableCharacterBase::InteractPressCompleted_Implementation()
{
	InteractableComponent->InteractPressCompleted();
}

float AInteractableCharacterBase::InteractHoldStarted_Implementation(AActor* OtherInstigator)
{
	return InteractableComponent->InteractHoldStarted(OtherInstigator);
}

void AInteractableCharacterBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
	InteractableComponent->InteractHoldOngoing(ElapsedSeconds);
}

void AInteractableCharacterBase::InteractHoldTriggered_Implementation()
{
	InteractableComponent->InteractHoldTriggered();
}

void AInteractableCharacterBase::InteractHoldCanceled_Implementation()
{
	InteractableComponent->InteractHoldCanceled();
}

void AInteractableCharacterBase::InteractHoldCompleted_Implementation()
{
	InteractableComponent->InteractHoldCompleted();
}

bool AInteractableCharacterBase::DoesUseCustomInteractArea_Implementation()
{
	return InteractableComponent->DoesUseCustomInteractArea();
}

void AInteractableCharacterBase::SetCanInteract_Implementation(const bool bNewCanInteract)
{
	InteractableComponent->SetCanInteract(bNewCanInteract);
}

bool AInteractableCharacterBase::GetCanInteract_Implementation()
{
	return InteractableComponent->GetCanInteract();
}

EInteractType AInteractableCharacterBase::GetInteractType_Implementation()
{
	return InteractableComponent->GetInteractType();
}

