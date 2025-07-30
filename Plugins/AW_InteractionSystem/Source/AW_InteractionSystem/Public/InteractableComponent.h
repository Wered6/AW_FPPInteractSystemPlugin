// Copyright (c) 2025 Arek.Wered;

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class UWidgetComponent;
class UInteractIconWidget;

/**
 * This component provides support for implementing interactable objects and handling player interaction logic.
 * Only for InteractableActorBase, InteractablePawnBase, InteractableCharacterBase.
 */
UCLASS(NotBlueprintable, NotBlueprintType)
class AW_INTERACTIONSYSTEM_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	DECLARE_LOG_CATEGORY_CLASS(LogInteractableComponent, Error, All);

protected:
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	FORCEINLINE void SetInteractInstigator(AActor* Instigator)
	{
		InteractInstigator = Instigator;
	}

	FORCEINLINE AActor* GetInteractInstigator() const
	{
		return InteractInstigator;
	}

	UFUNCTION(BlueprintCallable, Category=Interact)
	void AddOutlineMeshComponent(UMeshComponent* MeshComponent);
	UFUNCTION(BlueprintCallable, Category=Interact)
	void SetOutlineMeshComponents(const TArray<UMeshComponent*>& NewOutlineMeshComponents);

	UPROPERTY(EditAnywhere, Category=Interact)
	EInteractType InteractType{};

	UPROPERTY(EditAnywhere, Category=Interact)
	FVector2D IconSize{50.f, 50.f};

	UPROPERTY(EditAnywhere, Category=Interact, meta=(UIMin=0, UIMax=1, ClampMin=0, ClampMax=1, EditCondition="InteractType == EInteractType::Hold"))
	float MinIconOpacity{0.3f};
	UPROPERTY(EditAnywhere, Category=Interact, meta=(UIMin=0, UIMax=1, ClampMin=0, ClampMax=1, EditCondition="InteractType == EInteractType::Hold"))
	float MinProgressCircleOpacity{};
	UPROPERTY(EditAnywhere, Category=Interact, meta=(EditCondition="InteractType == EInteractType::Hold"))
	FVector2D ProgressCircleSize{100.f, 100.f};

	UPROPERTY(EditAnywhere, Category=Interact, meta=(UIMin=0, ClampMin=0, EditCondition="InteractType == EInteractType::Hold"))
	float HoldTimeThreshold{};

	UPROPERTY(EditAnywhere, Category=Interact)
	bool bCanInteract{true};
	UPROPERTY(EditAnywhere, Category=Interact)
	bool bUseCustomInteractArea{false};

private:
	void InitializeInteractWidget();
	void UpdateWidgetAttachment() const;

	void UpdateOutline(const bool bHighlight);

	UPROPERTY(VisibleInstanceOnly, Category=Interact)
	TObjectPtr<AActor> InteractInstigator;

	UPROPERTY()
	TArray<TObjectPtr<UMeshComponent>> OutlineMeshComponents;

	UPROPERTY(EditDefaultsOnly, meta=(DisplayPriority=0), Category=Interact)
	TSubclassOf<UInteractIconWidget> InteractIconWidgetClass;

	UPROPERTY()
	TObjectPtr<UInteractIconWidget> InteractIconWidget;
	UPROPERTY()
	TObjectPtr<UWidgetComponent> InteractIconWidgetComponent;

#pragma region InteractInterface

public:
	void DisplayInteractionUI(const bool bShowInteract);

	void InteractPressStarted(AActor* OtherInstigator);
	void InteractPressTriggered();
	void InteractPressCompleted();

	float InteractHoldStarted(AActor* OtherInstigator);
	void InteractHoldOngoing(const float ElapsedSeconds);
	void InteractHoldTriggered();
	void InteractHoldCanceled();
	void InteractHoldCompleted();

	bool DoesUseCustomInteractArea() const;
	void SetCanInteract(const bool bNewCanInteract);
	bool GetCanInteract() const;
	EInteractType GetInteractType() const;

#pragma endregion
};
