// Copyright (c) 2025 Arek.Wered;

#pragma once

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	Press,
	Hold
};

UENUM(BlueprintType)
enum class EInteractCategory : uint8
{
	Use,
	Collect,
	Open,
	Unlock
};
