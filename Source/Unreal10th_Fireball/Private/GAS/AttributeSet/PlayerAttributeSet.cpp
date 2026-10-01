// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/PlayerAttributeSet.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
    InitHealth(100.0f);
    InitMaxHealth(100.0f);

    InitMana(100.0f);
    InitMaxMana(100.0f);

    InitDamage(0.0f);
    InitManaCost(0.0f);
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
    else if (Attribute == GetManaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
    }
}

void UPlayerAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        UE_LOG(LogTemp, Log, TEXT("[UPlayerAttributeSet::PostAttributeChange()] : Health 변경됨 (%.1f) -> (%.1f)"),
               OldValue, NewValue);
    }
    else if (Attribute == GetManaAttribute())
    {
        UE_LOG(LogTemp, Log, TEXT("[UPlayerAttributeSet::PostAttributeChange()] : Mana 변경됨 (%.1f) -> (%.1f)"),
               OldValue, NewValue);
    }
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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
    else if (Data.EvaluatedData.Attribute == GetManaCostAttribute())
    {
        const float LocalManaCost = GetManaCost();
        SetManaCost(0.0f);

        if (LocalManaCost > 0)
        {
            float FinalManaCost = LocalManaCost;
            FinalManaCost = FMath::Max(0.0f, FinalManaCost);

            const float NewMana = FMath::Clamp(GetMana() - FinalManaCost, 0.0f, GetMaxMana());
            SetMana(NewMana);
        }
    }
}
