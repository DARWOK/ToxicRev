// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableBase.h"
#include "ThrowableDataAsset.h"
#include "ToxinCloud.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AThrowableBase::AThrowableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->OnComponentHit.AddDynamic(this, &AThrowableBase::OnHit);

    Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
    Projectile->bRotationFollowsVelocity = true;
    Projectile->ProjectileGravityScale = 1.f;
}

// Called when the game starts or when spawned
void AThrowableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowableBase::ArmAndThrow(const FVector& Dir, float Power)
{
    if (Config)
    {
        Projectile->InitialSpeed = Config->InitialSpeed * Power;
        Projectile->MaxSpeed = Projectile->InitialSpeed;
        Projectile->ProjectileGravityScale = Config->GravityScale;
    }
    Mesh->AddImpulse(Dir * Projectile->InitialSpeed, NAME_None, true);
}

void AThrowableBase::OnHit(UPrimitiveComponent* HitComp, AActor* Other, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (Config && Config->bSticky && OtherComp)
    {
        Mesh->SetSimulatePhysics(false);
        AttachToComponent(OtherComp, FAttachmentTransformRules::KeepWorldTransform);
    }
    Explode();
}

void AThrowableBase::Explode()
{
    if (ExplosionFX) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, GetActorTransform());
    if (ExplosionSFX) UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSFX, GetActorLocation());

    if (Config && Config->BaseDamage > 0.f)
    {
        TArray<AActor*> Ignore;
        UGameplayStatics::ApplyRadialDamage(GetWorld(), Config->BaseDamage, GetActorLocation(),
            Config->ExplosionRadius, nullptr, Ignore, this, GetInstigatorController(), true);
    }

    if (Config && Config->bAppliesToxin && CloudClass)
    {
        FActorSpawnParameters P; P.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AToxinCloud* Cloud = GetWorld()->SpawnActor<AToxinCloud>(CloudClass, GetActorTransform(), P);
        if (Cloud)
        {
            Cloud->Radius = Config->CloudRadius;
            Cloud->DPS = Config->DoTDPS;
            Cloud->Duration = Config->DoTDuration;
            Cloud->BeginCloud();
        }
    }
    Destroy();
}