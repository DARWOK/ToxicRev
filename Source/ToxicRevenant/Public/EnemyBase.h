// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class TOXICREVENANT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy") int32 Health = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy") float ToxinResistance = 0.f; // 0..100
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy") int32 BountySamples = 5;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void TakeDamageSimple(float Amount);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnDied();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
