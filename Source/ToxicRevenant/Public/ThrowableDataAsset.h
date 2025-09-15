// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ThrowableDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOXICREVENANT_API UThrowableDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throwable") FName Name = "Default";
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throwable") float InitialSpeed = 1200.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throwable") float GravityScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion") float ExplosionRadius = 250.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion") float BaseDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toxin") bool bAppliesToxin = true;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toxin", meta = (EditCondition = "bAppliesToxin")) float DoTDPS = 4.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toxin", meta = (EditCondition = "bAppliesToxin")) float DoTDuration = 3.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toxin", meta = (EditCondition = "bAppliesToxin")) float CloudRadius = 220.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags") bool bSticky = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags") bool bCorrosive = false;
};
