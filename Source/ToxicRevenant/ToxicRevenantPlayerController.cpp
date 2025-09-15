// Copyright Epic Games, Inc. All Rights Reserved.


#include "ToxicRevenantPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ToxicRevenantCameraManager.h"

AToxicRevenantPlayerController::AToxicRevenantPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AToxicRevenantCameraManager::StaticClass();
}

void AToxicRevenantPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
