// Copyright Epic Games, Inc. All Rights Reserved.

#include "AW_InteractionSystem.h"

#define LOCTEXT_NAMESPACE "FAW_InteractionSystemModule"

void FAW_InteractionSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAW_InteractionSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAW_InteractionSystemModule, AW_InteractionSystem)