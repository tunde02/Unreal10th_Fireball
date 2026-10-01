// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/EnemyAttributeSet.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
    InitHealth(100.0f);
    InitMaxHealth(100.0f);

    InitDamage(0.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
}

void UEnemyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        UE_LOG(LogTemp, Log, TEXT("[UEnemyAttributeSet::PostAttributeChange()] : Health 변경됨 (%.1f) -> (%.1f)"),
               OldValue, NewValue);
    }
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        const float LocalDamage = GetDamage();
        SetDamage(0.0f);

        if (LocalDamage > 0)
        {
            float FinalDamage = LocalDamage;
            FinalDamage = FMath::Max(0.0f, FinalDamage);

            const float NewHealth = FMath::Clamp(GetHealth() - FinalDamage, 0.0f, GetMaxHealth());
            SetHealth(NewHealth);
        }
    }
}
