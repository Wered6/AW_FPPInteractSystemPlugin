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

	// TODO draw debug message in a corner
	TWeakObjectPtr<AActor> InteractableActor;
	TWeakObjectPtr<UPrimitiveComponent> InteractableHitComponent;

	UPROPERTY(EditAnywhere, Category=Interact)
	float InteractionDistance{200.f};
	UPROPERTY(VisibleAnywhere, Category=Interact)
	bool bCanCheckInteraction{true};

	TWeakObjectPtr<APawn> PawnOwner;
	TWeakObjectPtr<APlayerController> PlayerController;

#pragma region Input

	void InteractPressStarted();
	void InteractPressTriggered();
	void InteractPressCompleted();

	void InteractHoldStarted(const FInputActionInstance& Instance);
	void InteractHoldOngoing(const FInputActionInstance& Instance);
	void InteractHoldCanceled();
	void InteractHoldTriggered();
	void InteractHoldCompleted();

	UPROPERTY(EditDefaultsOnly, Category=Interact)
	TObjectPtr<UInputMappingContext> InteractMappingContext;
	UPROPERTY(EditDefaultsOnly, Category=Interact)
	TObjectPtr<UInputAction> InteractPressAction;
	UPROPERTY(EditDefaultsOnly, Category=Interact)
	TObjectPtr<UInputAction> InteractHoldAction;

	bool bIsHolding{false};

#pragma endregion
};
