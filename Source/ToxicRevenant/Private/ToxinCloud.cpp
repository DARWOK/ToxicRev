// Fill out your copyright notice in the Description page of Project Settings.


#include "ToxinCloud.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AToxinCloud::AToxinCloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Area = CreateDefaultSubobject<USphereComponent>(TEXT("Area"));
	SetRootComponent(Area);
	Area->InitSphereRadius(Radius);
	Area->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Area->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AToxinCloud::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToxinCloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToxinCloud::BeginCloud()
{
    Area->SetSphereRadius(Radius);
    // Tick cada 1s
    GetWorldTimerManager().SetTimer(TickHandle, this, &AToxinCloud::TickDamage, 1.0f, true);
    // Vida total
    GetWorldTimerManager().SetTimer(LifetimeHandle, [this]()
        {
            GetWorldTimerManager().ClearTimer(TickHandle);
            Destroy();
        }, Duration, false);
}

void AToxinCloud::TickDamage()
{
    TArray<AActor*> Overlapping;
    Area->GetOverlappingActors(Overlapping);
    for (AActor* A : Overlapping)
    {
        UGameplayStatics::ApplyDamage(A, DPS, nullptr, this, nullptr);
    }
}