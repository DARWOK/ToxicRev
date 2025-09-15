// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOXICREVENANT_API UObjectPoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Pool")
    AActor* AcquireActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform);

    UFUNCTION(BlueprintCallable, Category = "Pool")
    void ReleaseActor(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "Pool")
    void Prewarm(TSubclassOf<AActor> ActorClass, int32 Count, const FTransform& SpawnTransform);

private:
    TMap<TSubclassOf<AActor>, TArray<TWeakObjectPtr<AActor>>> Pool;
};
