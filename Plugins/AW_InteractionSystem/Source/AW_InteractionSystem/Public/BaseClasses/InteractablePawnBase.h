// Copyright (c) 2025 Arek.Wered;

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Pawn.h"
#include "InteractablePawnBase.generated.h"

class UInteractableComponent;

UCLASS()
class AW_INTERACTIONSYSTEM_API AInteractablePawnBase : public APawn, public IInteractInterface
{
	GENERATED_BODY()

public:
	AInteractablePawnBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInteractableComponent> InteractableComponent;

#pragma region InteractInterface

public:
	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;

	virtual void InteractPressStarted_Implementation(AActor* OtherInstigator) override;
	virtual void InteractPressTriggered_Implementation() override;
	virtual void InteractPressCompleted_Implementation() override;

	virtual float InteractHoldStarted_Implementation(AActor* OtherInstigator) override;
	virtual void InteractHoldOngoing_Implementation(const float ElapsedSeconds) override;
	virtual void InteractHoldTriggered_Implementation() override;
	virtual void InteractHoldCanceled_Implementation() override;
	virtual void InteractHoldCompleted_Implementation() override;

	virtual bool DoesUseCustomInteractArea_Implementation() override;
	virtual void SetCanInteract_Implementation(const bool bNewCanInteract) override;
	virtual bool GetCanInteract_Implementation() override;
	virtual EInteractType GetInteractType_Implementation() override;

#pragma endregion
};
