// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "PlayerAttributeSet.generated.h"

UCLASS()
class UNREAL10TH_FIREBALL_API UPlayerAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UPlayerAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
    UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, MaxHealth);

    UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, Mana);

    UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, MaxMana);

    UPROPERTY(BlueprintReadOnly, Category = "Meta Attribute")
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, Damage);

    UPROPERTY(BlueprintReadOnly, Category = "Meta Attribute")
    FGameplayAttributeData ManaCost;
    ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, ManaCost);

};
