// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "FireballProjectile.generated.h"

class UAbilitySystemComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class UNREAL10TH_FIREBALL_API AFireballProjectile : public AActor
{
    GENERATED_BODY()

public:
    AFireballProjectile();

    void InitializeFireballProjectile(
        UAbilitySystemComponent* InSourceASC,
        const FGameplayEffectSpecHandle& InDamageSpec,
        const FGameplayEffectSpecHandle& InBurnSpec);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UProjectileMovementComponent> Movement;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TObjectPtr<UNiagaraSystem> HitVFX;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    float Damage = 10.0f;

private:
    TWeakObjectPtr<UAbilitySystemComponent> SourceASC;
    FGameplayEffectSpecHandle DamageSpec;
    FGameplayEffectSpecHandle BurnSpec;

};
