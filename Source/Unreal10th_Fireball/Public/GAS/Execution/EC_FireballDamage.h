// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EC_FireballDamage.generated.h"

UCLASS()
class UNREAL10TH_FIREBALL_API UEC_FireballDamage : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:
    UEC_FireballDamage();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Fireball", meta = (Categories = "GAS"))
    FGameplayTag DamageTag;

    UPROPERTY(EditDefaultsOnly, Category = "Fireball", meta = (Categories = "GAS"))
    FGameplayTag BurnStateTag;

    UPROPERTY(EditDefaultsOnly, Category = "Fireball")
    float BurnDamageRate = 2.0f;

};
