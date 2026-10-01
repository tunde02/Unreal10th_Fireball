// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Execution/EC_FireballDamage.h"
#include "GAS/AttributeSet/EnemyAttributeSet.h"

UEC_FireballDamage::UEC_FireballDamage()
{
    DamageTag = FGameplayTag::RequestGameplayTag(FName("GAS.Data.Damage"), false);
    BurnStateTag = FGameplayTag::RequestGameplayTag(FName("GAS.State.Burn"), false);
}

void UEC_FireballDamage::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvalParams;
    EvalParams.TargetTags = TargetTags;

    // 1차 대미지 계산
    float Damage = Spec.GetSetByCallerMagnitude(DamageTag, false, 0.0f);

    // 타겟에게 Burn 태그가 있으면 대미지 2배
    if (TargetTags && TargetTags->HasTag(BurnStateTag))
    {
        Damage *= BurnDamageRate;
    }

    if (Damage > 0.0f)
    {
        OutExecutionOutput.AddOutputModifier(
            FGameplayModifierEvaluatedData(
                UEnemyAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, Damage));
    }
}
