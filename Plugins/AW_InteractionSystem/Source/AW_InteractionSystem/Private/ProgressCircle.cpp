// Copyright (c) 2025 Arek.Wered;


#include "ProgressCircle.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UProgressCircle::NativePreConstruct()
{
	Super::NativePreConstruct();

	MID_ProgressCircle = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MI_ProgressCircle);
	ProgressCircleImage->SetBrushFromMaterial(MID_ProgressCircle);
	SetPercent(Percent);
	SetBackgroundCircleOpacity(BackgroundCircleOpacity);
	SetImageSize(ImageSize);
}

void UProgressCircle::SetPercent(const float InPercent) const
{
	if (!MID_ProgressCircle)
	{
		return;
	}

	constexpr float MinPercent{0.f};
	constexpr float MaxPercent{1.f};
	MID_ProgressCircle->SetScalarParameterValue(FName("Percent"), FMath::Clamp(InPercent, MinPercent, MaxPercent));
}

void UProgressCircle::SetOpacity(const float InOpacity) const
{
	constexpr float MinOpacity{0.f};
	constexpr float MaxOpacity{1.f};
	MID_ProgressCircle->SetScalarParameterValue(FName("Opacity"), FMath::Clamp(InOpacity, MinOpacity, MaxOpacity));
}

void UProgressCircle::SetImageSize(const FVector2D InImageSize) const
{
	ProgressCircleImage->SetDesiredSizeOverride(InImageSize);
}

void UProgressCircle::SetBackgroundCircleOpacity(const float InOpacity) const
{
	MID_ProgressCircle->SetScalarParameterValue(FName("BackgroundCircleOpacity"), InOpacity);
}
