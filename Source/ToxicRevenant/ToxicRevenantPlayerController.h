// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToxicRevenantPlayerController.generated.h"

class UInputMappingContext;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract)
class TOXICREVENANT_API AToxicRevenantPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AToxicRevenantPlayerController();

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

};
