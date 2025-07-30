// Copyright (c) 2025 Arek.Wered;


#include "InteractIconWidget.h"
#include "ProgressCircle.h"
#include "Components/Image.h"

void UInteractIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

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

void UInteractIconWidget::Init(
	const EInteractType NewInteractType,
	const float NewMinIconOpacity,
	const FVector2D NewIconSize,
	const float NewMinProgressCircleOpacity,
	const FVector2D NewProgressCircleSize)
{
	InteractType = NewInteractType;
	MinIconOpacity = NewMinIconOpacity;
	IconSize = NewIconSize;
	MinProgressCircleOpacity = NewMinProgressCircleOpacity;
	ProgressCircleSize = NewProgressCircleSize;
}

void UInteractIconWidget::SetIconSize(const FVector2D Size) const
{
	Icon->SetDesiredSizeOverride(Size);
}

void UInteractIconWidget::SetIconOpacity(const float Opacity)
{
	constexpr float MinClampOpacity{0.f};
	constexpr float MaxClampOpacity{1.f};
	const float Alpha{FMath::Clamp(Opacity, MinClampOpacity, MaxClampOpacity)};

	const float MinLerpOpacity{MinIconOpacity};
	constexpr float MaxLerpOpacity{1.f};
	CurrentIconOpacity = FMath::Lerp(MinLerpOpacity, MaxLerpOpacity, Alpha);

	Icon->SetOpacity(CurrentIconOpacity);
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
