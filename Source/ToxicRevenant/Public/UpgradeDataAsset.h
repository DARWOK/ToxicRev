// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeDataAsset.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	DoTDPS      UMETA(DisplayName = "DoT DPS"),
	DoTDuration UMETA(DisplayName = "DoT Duration"),
	CloudRadius UMETA(DisplayName = "Cloud Radius"),
	Utility     UMETA(DisplayName = "Utility")
};

UCLASS(BlueprintType)
class TOXICREVENANT_API UUpgradeDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade") FName Name = "Upgrade";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade") int32 Cost = 50;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade") EUpgradeType Type = EUpgradeType::DoTDPS;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade") float Magnitude = 0.15f; // 15%
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade") FString EffectDescription;
};
