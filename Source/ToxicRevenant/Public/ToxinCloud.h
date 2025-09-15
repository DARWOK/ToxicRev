// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToxinCloud.generated.h"

class USphereComponent;

UCLASS()
class TOXICREVENANT_API AToxinCloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToxinCloud();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp") USphereComponent* Area;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toxin") float Radius = 220.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toxin") float DPS = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toxin") float Duration = 3.5f;

	UFUNCTION(BlueprintCallable, Category = "Toxin")
	void BeginCloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TickHandle;
	FTimerHandle LifetimeHandle;

	void TickDamage();
};
