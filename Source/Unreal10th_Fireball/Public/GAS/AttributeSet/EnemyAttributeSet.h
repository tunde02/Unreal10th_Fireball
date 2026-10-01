// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "EnemyAttributeSet.generated.h"

UCLASS()
class UNREAL10TH_FIREBALL_API UEnemyAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UEnemyAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
    UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS_BASIC(UEnemyAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS_BASIC(UEnemyAttributeSet, MaxHealth);

    UPROPERTY(BlueprintReadOnly, Category = "Meta Attribute")
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS_BASIC(UEnemyAttributeSet, Damage);

};
