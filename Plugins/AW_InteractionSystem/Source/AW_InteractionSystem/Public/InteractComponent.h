// Copyright (c) 2025 Arek.Wered;

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionInstance;

UCLASS(ClassGroup=(Interact), meta=(BlueprintSpawnableComponent), DisplayName="Interact Component")
class AW_INTERACTIONSYSTEM_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE void SetCanCheckInteraction(const bool bValue)
	{
		bCanCheckInteraction = bValue;
	}

private:
	void PerformInteractionCheck();
	void SetInteraction(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	void ClearInteraction();

	UPROPERTY(VisibleAnywhere, Category=Interact)
	TObjectPtr<AActor> InteractableActor;
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> InteractableHitComponent;

	UPROPERTY(EditAnywhere, Category=Interact)
	float InteractionDistance{200.f};
	UPROPERTY(VisibleAnywhere, Category=Interact)
	bool bCanCheckInteraction{true};

	UPROPERTY()
	TObjectPtr<APawn> PawnOwner;
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

#pragma region Input

	void InteractPressStarted();
	void InteractPressTriggered();
	void InteractPressCompleted();

	void InteractHoldStarted(const FInputActionInstance& Instance);
	void InteractHoldOngoing(const FInputActionInstance& Instance);
	void InteractHoldCanceled();
	void InteractHoldTriggered();
	void InteractHoldCompleted();

	UPROPERTY(EditDefaultsOnly, Category="Interact|Input")
	TObjectPtr<UInputMappingContext> InteractMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Interact|Input")
	TObjectPtr<UInputAction> InteractPressAction;
	UPROPERTY(EditDefaultsOnly, Category="Interact|Input")
	TObjectPtr<UInputAction> InteractHoldAction;

	bool bIsHolding{false};

#pragma endregion
};
