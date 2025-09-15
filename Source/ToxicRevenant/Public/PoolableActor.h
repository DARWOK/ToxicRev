// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableActor.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class TOXICREVENANT_API UPoolableActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOXICREVENANT_API IPoolableActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pool")
    void OnAcquireFromPool();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pool")
    void OnReleaseToPool();
};
