// Copyright (c) 2025 Arek.Wered;

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressCircle.generated.h"

class UImage;
/**
 *
 */
UCLASS()
class AW_INTERACTIONSYSTEM_API UProgressCircle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	/**
	 * Sets the percentage of the foreground circle.
	 */
	UFUNCTION(BlueprintCallable)
	void SetPercent(const float InPercent) const;

	/*
	 * Sets the opacity of the foreground circle.
	 */
	UFUNCTION(BlueprintCallable)
	void SetOpacity(const float InOpacity) const;

	UFUNCTION(BlueprintCallable)
	void SetImageSize(const FVector2D InImageSize) const;
	UFUNCTION(BlueprintCallable)
	void SetBackgroundCircleOpacity(const float InOpacity) const;

private:
	/**
	 * Percentage of the foreground circle.
	 */
	UPROPERTY(EditAnywhere, meta=(UIMin=0, UIMax=1, ClampMin=0, ClampMax=1))
	float Percent{0.5f};
	/**
	 * Opacity of the foreground circle.
	 */
	UPROPERTY(EditAnywhere, meta=(UIMin=0, UIMax=1, ClampMin=0, ClampMax=1))
	float Opacity{1.f};
	UPROPERTY(EditAnywhere)
	FVector2D ImageSize{32.f, 32.f};
	UPROPERTY(EditAnywhere, meta=(UIMin=0, UIMax=1, ClampMin=0, ClampMax=1))
	float BackgroundCircleOpacity{0.2f};

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MID_ProgressCircle;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> MI_ProgressCircle;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ProgressCircleImage;
};
