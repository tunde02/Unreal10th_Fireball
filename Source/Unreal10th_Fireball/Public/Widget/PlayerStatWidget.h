// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "PlayerStatWidget.generated.h"

class UAbilitySystemComponent;
class UProgressBar;
class UTextBlock;

UCLASS()
class UNREAL10TH_FIREBALL_API UPlayerStatWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void BindToASC(UAbilitySystemComponent* InASC);

private:
    void UpdateHealthUI(float InCurrent, float InMax);
    void UpdateManaUI(float InCurrent, float InMax);

    void OnHealthChanged(const FOnAttributeChangeData& Data);
    void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
    void OnManaChanged(const FOnAttributeChangeData& Data);
    void OnMaxManaChanged(const FOnAttributeChangeData& Data);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UProgressBar> HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UTextBlock> HealthText;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UProgressBar> ManaProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UTextBlock> ManaText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentHealth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentMana = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxMana = 0.0f;

};
