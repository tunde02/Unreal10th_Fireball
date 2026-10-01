// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Fireball.generated.h"

class AFireballProjectile;

UCLASS()
class UNREAL10TH_FIREBALL_API UGameplayAbility_Fireball : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGameplayAbility_Fireball();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    virtual bool CheckCost(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Fireball")
    TSubclassOf<AFireballProjectile> FireballProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Fireball")
    TSubclassOf<UGameplayEffect> FireballDamageEffectClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Fireball")
    TSubclassOf<UGameplayEffect> FireballBurnEffectClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Fireball")
    float FireballDamage = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Fireball")
    float BurnDamage = 1.0f;

};
