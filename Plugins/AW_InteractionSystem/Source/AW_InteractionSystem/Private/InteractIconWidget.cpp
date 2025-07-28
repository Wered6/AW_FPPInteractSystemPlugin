// Copyright (c) 2025 Arek.Wered;


#include "InteractIconWidget.h"
#include "ProgressCircle.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

void UInteractIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetInteractCategory(InteractCategory);

	switch (InteractType)
	{
	case EInteractType::Press:
		ProgressCircle->SetVisibility(ESlateVisibility::Collapsed);
		SetIconOpacity(1.f);
		break;
	case EInteractType::Hold:
		ProgressCircle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SetIconOpacity(0.f);
		SetProgressCircleOpacity(0.f);
		SetProgressCirclePercent(0.f);
		SetProgressCircleSize(ProgressCircleSize);
		break;
	}

	SetIconSize(IconSize);
}

void UInteractIconWidget::Init(const EInteractCategory NewInteractCategory,
                               const EInteractType NewInteractType,
                               const float NewMinIconOpacity,
                               const FVector2D NewIconSize,
                               const float NewMinProgressCircleOpacity,
                               const FVector2D NewProgressCircleSize)
{
	InteractCategory = NewInteractCategory;
	InteractType = NewInteractType;
	MinIconOpacity = NewMinIconOpacity;
	MinProgressCircleOpacity = NewMinProgressCircleOpacity;
	ProgressCircleSize = NewProgressCircleSize;
}

void UInteractIconWidget::SetInteractCategory(const EInteractCategory InInteractCategory)
{
	switch (InInteractCategory)
	{
	case EInteractCategory::Use:
		IconSwitcher->SetActiveWidget(UseIcon);
		break;
	case EInteractCategory::Collect:
		IconSwitcher->SetActiveWidget(CollectIcon);
		break;
	case EInteractCategory::Open:
		IconSwitcher->SetActiveWidget(OpenIcon);
		break;
	case EInteractCategory::Unlock:
		IconSwitcher->SetActiveWidget(UnlockIcon);
		break;
	}
}

void UInteractIconWidget::SetIconSize(const FVector2D Size) const
{
	for (UWidget* Icon : IconSwitcher->GetAllChildren())
	{
		if (UImage* ImageIcon{Cast<UImage>(Icon)})
		{
			ImageIcon->SetDesiredSizeOverride(Size);
		}
	}
}

void UInteractIconWidget::SetIconOpacity(const float Opacity)
{
	constexpr float MinClampOpacity{0.f};
	constexpr float MaxClampOpacity{1.f};
	const float Alpha{FMath::Clamp(Opacity, MinClampOpacity, MaxClampOpacity)};

	const float MinLerpOpacity{MinIconOpacity};
	constexpr float MaxLerpOpacity{1.f};
	CurrentIconOpacity = FMath::Lerp(MinLerpOpacity, MaxLerpOpacity, Alpha);

	IconSwitcher->SetRenderOpacity(CurrentIconOpacity);
}

void UInteractIconWidget::SetProgressCircleSize(const FVector2D Size) const
{
	ProgressCircle->SetImageSize(Size);
}

void UInteractIconWidget::SetProgressCircleOpacity(const float Opacity)
{
	constexpr float MinClampOpacity{0.f};
	constexpr float MaxClampOpacity{1.f};
	const float Alpha{FMath::Clamp(Opacity, MinClampOpacity, MaxClampOpacity)};

	const float MinLerpOpacity{MinProgressCircleOpacity};
	constexpr float MaxLerpOpacity{1.f};
	CurrentProgressCircleOpacity = FMath::Lerp(MinLerpOpacity, MaxLerpOpacity, Alpha);
}

void UInteractIconWidget::SetProgressCirclePercent(const float Percent)
{
	constexpr float MinClampPercent{0.f};
	constexpr float MaxClampPercent{1.f};
	const float ClampedPercent{FMath::Clamp(Percent, MinClampPercent, MaxClampPercent)};

	CurrentProgressCirclePercent = ClampedPercent;
	ProgressCircle->SetPercent(CurrentProgressCirclePercent);
}
