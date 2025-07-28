// Copyright (c) 2025 Arek.Wered;

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

enum class EInteractType : uint8;

UINTERFACE()
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class IInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interact)
	void DisplayInteractionUI(const bool bShowInteract);

	UFUNCTION(BlueprintNativeEvent, Category="Interact|Press")
	void InteractPressStarted(AActor* OtherInstigator);
	UFUNCTION(BlueprintNativeEvent, Category="Interact|Press")
	void InteractPressTriggered();
	UFUNCTION(BlueprintNativeEvent, Category="Interact|Press")
	void InteractPressCompleted();

	UFUNCTION(BlueprintNativeEvent, Category="Interact|Hold", meta=(ReturnDisplayName=HoldTimeThreshold))
	float InteractHoldStarted(AActor* OtherInstigator);
	UFUNCTION(BlueprintNativeEvent, Category="Interact|Hold")
	void InteractHoldOngoing(const float ElapsedSeconds);
	UFUNCTION(BlueprintNativeEvent, Category="Interact|Hold")
	void InteractHoldCanceled();
	UFUNCTION(BlueprintNativeEvent, Category="Interact|Hold")
	void InteractHoldTriggered();
	UFUNCTION(BlueprintNativeEvent, Category="Interact|Hold")
	void InteractHoldCompleted();

	UFUNCTION(BlueprintNativeEvent, Category=Interact)
	USceneComponent* GetWidgetAttachmentComponent();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interact)
	bool DoesUseCustomInteractArea();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interact)
	void SetCanInteract(const bool bNewCanInteract);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interact)
	bool GetCanInteract();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interact)
	EInteractType GetInteractType();
};
