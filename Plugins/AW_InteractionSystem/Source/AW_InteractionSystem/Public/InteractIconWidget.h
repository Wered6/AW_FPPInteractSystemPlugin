// Copyright (c) 2025 Arek.Wered;

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Blueprint/UserWidget.h"
#include "InteractIconWidget.generated.h"

class UImage;
class UWidgetSwitcher;
class UProgressCircle;

/**
 *
 */
UCLASS()
class AW_INTERACTIONSYSTEM_API UInteractIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void Init(const EInteractCategory NewInteractCategory,
	          const EInteractType NewInteractType,
	          const float NewMinIconOpacity,
	          const FVector2D NewIconSize,
	          const float NewMinProgressCircleOpacity,
	          const FVector2D NewProgressCircleSize);

	void SetInteractCategory(const EInteractCategory InInteractCategory);
	void SetIconSize(const FVector2D Size) const;
	void SetIconOpacity(const float Opacity);

	void SetProgressCircleSize(const FVector2D Size) const;
	void SetProgressCircleOpacity(const float Opacity);
	void SetProgressCirclePercent(const float Percent);

private:
	UPROPERTY(EditAnywhere, Category=Interact)
	EInteractCategory InteractCategory;
	UPROPERTY(EditAnywhere, Category=Interact)
	EInteractType InteractType;

	UPROPERTY(EditAnywhere, Category=Interact)
	FVector2D IconSize{50.f, 50.f};

	UPROPERTY(EditAnywhere, Category=Interact, meta=(EditCondition="InteractType == EInteractType::Hold", UIMin=0, UIMax=1, ClampMin=0, ClampMax=1))
	float MinIconOpacity{0.3f};
	UPROPERTY(EditAnywhere, Category=Interact, meta=(EditCondition="InteractType == EInteractType::Hold"))
	FVector2D ProgressCircleSize{100.f, 100.f};
	UPROPERTY(EditAnywhere, Category=Interact, meta=(EditCondition="InteractType == EInteractType::Hold", UIMin=0, UIMax=1, ClampMin=0, ClampMax=1))
	float MinProgressCircleOpacity{0.f};

	UPROPERTY(VisibleAnywhere, Category=Interact)
	float CurrentIconOpacity{};
	UPROPERTY(VisibleAnywhere, Category=Interact)
	float CurrentProgressCircleOpacity{};
	UPROPERTY(VisibleAnywhere, Category=Interact)
	float CurrentProgressCirclePercent{};

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressCircle> ProgressCircle;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> IconSwitcher;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> CollectIcon;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> OpenIcon;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> UseIcon;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> UnlockIcon;
};
