// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "OverheadHealthWidget.generated.h"

class UAbilitySystemComponent;
class UProgressBar;
class UTextBlock;

UCLASS()
class UNREAL10TH_FIREBALL_API UOverheadHealthWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void BindToASC(UAbilitySystemComponent* InASC);

private:
    void UpdateHealthUI(float InCurrent, float InMax);

    void OnHealthChanged(const FOnAttributeChangeData& Data);
    void OnMaxHealthChanged(const FOnAttributeChangeData& Data);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UProgressBar> HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UTextBlock> HealthText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentHealth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 0.0f;

};
