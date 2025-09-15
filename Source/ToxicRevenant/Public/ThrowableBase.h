// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableBase.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UThrowableDataAsset;
class AToxinCloud;

UCLASS()
class TOXICREVENANT_API AThrowableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp") UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp") UProjectileMovementComponent* Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config") UThrowableDataAsset* Config;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FX") UParticleSystem* ExplosionFX = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FX") USoundBase* ExplosionSFX = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config") TSubclassOf<AToxinCloud> CloudClass;

	UFUNCTION(BlueprintCallable, Category = "Throwable")
	void ArmAndThrow(const FVector& Direction, float Power = 1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
