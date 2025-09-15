// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolSubsystem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PoolableActor.h"

static void SetPooledState(AActor* Actor, bool bActive)
{
    if (!Actor) return;
    Actor->SetActorHiddenInGame(!bActive);
    Actor->SetActorEnableCollision(bActive);
    Actor->SetActorTickEnabled(bActive);
}

AActor* UObjectPoolSubsystem::AcquireActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform)
{
    if (!ActorClass) return nullptr;
    UWorld* World = GetWorld(); if (!World) return nullptr;

    // Limpia nulos
    TArray<TWeakObjectPtr<AActor>>& FreeList = Pool.FindOrAdd(ActorClass);
    FreeList.RemoveAll([](const TWeakObjectPtr<AActor>& P) { return !P.IsValid(); });

    AActor* Instance = nullptr;
    if (FreeList.Num() > 0)
    {
        Instance = FreeList.Pop().Get();
        Instance->SetActorTransform(SpawnTransform);
    }
    else
    {
        FActorSpawnParameters Params; Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Instance = World->SpawnActor<AActor>(ActorClass, SpawnTransform, Params);
    }

    SetPooledState(Instance, /*Active*/true);

    if (Instance && Instance->GetClass()->ImplementsInterface(UPoolableActor::StaticClass()))
    {
        IPoolableActor::Execute_OnAcquireFromPool(Instance);
    }
    return Instance;
}

void UObjectPoolSubsystem::ReleaseActor(AActor* Actor)
{
    if (!Actor) return;
    if (Actor->GetClass()->ImplementsInterface(UPoolableActor::StaticClass()))
    {
        IPoolableActor::Execute_OnReleaseToPool(Actor);
    }

    SetPooledState(Actor, /*Active*/false);
    Actor->SetActorLocation(FVector(0, 0, -100000)); // “Parking” debajo del mapa

    TArray<TWeakObjectPtr<AActor>>& FreeList = Pool.FindOrAdd(Actor->GetClass());
    FreeList.Add(Actor);
}

void UObjectPoolSubsystem::Prewarm(TSubclassOf<AActor> ActorClass, int32 Count, const FTransform& SpawnTransform)
{
    UWorld* World = GetWorld(); if (!World || !ActorClass) return;
    for (int32 i = 0; i < Count; ++i)
    {
        AActor* A = AcquireActor(ActorClass, SpawnTransform);
        ReleaseActor(A);
    }
}