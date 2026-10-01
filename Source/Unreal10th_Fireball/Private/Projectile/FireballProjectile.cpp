// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FireballProjectile.h"
#include "Character/GASCharacter.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AFireballProjectile::AFireballProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 0.35f));

    Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
    Movement->InitialSpeed = 1000.0f;
    Movement->MaxSpeed = 1000.0f;
    Movement->ProjectileGravityScale = 0.0f;
    Movement->Velocity = FVector::ForwardVector;
}

void AFireballProjectile::InitializeFireballProjectile(
    UAbilitySystemComponent* InSourceASC,
    const FGameplayEffectSpecHandle& InDamageSpec,
    const FGameplayEffectSpecHandle& InBurnSpec)
{
    SourceASC = InSourceASC;
    DamageSpec = InDamageSpec;
    BurnSpec = InBurnSpec;
}

void AFireballProjectile::BeginPlay()
{
    Super::BeginPlay();

    OnActorHit.AddDynamic(this, &AFireballProjectile::OnHit);

    if (GetInstigator())
    {
        Mesh->IgnoreActorWhenMoving(GetInstigator(), true);
    }

    SetLifeSpan(4.0f);
}

void AFireballProjectile::OnHit(
    AActor* SelfActor,
    AActor* OtherActor,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (OtherActor->IsA<AGASCharacter>() && OtherActor != GetOwner())
    {
        if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor))
        {
            UAbilitySystemComponent* TargetASC = ASI->GetAbilitySystemComponent();

            if (SourceASC.IsValid() && TargetASC)
            {
                SourceASC->ApplyGameplayEffectSpecToTarget(*DamageSpec.Data.Get(), TargetASC);
                SourceASC->ApplyGameplayEffectSpecToTarget(*BurnSpec.Data.Get(), TargetASC);

                Destroy();
            }
        }
    }
}
