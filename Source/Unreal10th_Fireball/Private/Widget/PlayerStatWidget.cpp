// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStatWidget.h"
#include "GAS/AttributeSet/PlayerAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerStatWidget::BindToASC(UAbilitySystemComponent* InASC)
{
    if (!InASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[UPlayerStatWidget::BindToASC()] : ASC가 nullptr입니다."));
        return;
    }

    InASC->GetGameplayAttributeValueChangeDelegate(
        UPlayerAttributeSet::GetHealthAttribute()).AddUObject(this, &UPlayerStatWidget::OnHealthChanged);

    InASC->GetGameplayAttributeValueChangeDelegate(
        UPlayerAttributeSet::GetMaxHealthAttribute())
        .AddUObject(this, &UPlayerStatWidget::OnMaxHealthChanged);

    InASC->GetGameplayAttributeValueChangeDelegate(
        UPlayerAttributeSet::GetManaAttribute()).AddUObject(this, &UPlayerStatWidget::OnManaChanged);

    InASC->GetGameplayAttributeValueChangeDelegate(
        UPlayerAttributeSet::GetMaxManaAttribute())
        .AddUObject(this, &UPlayerStatWidget::OnMaxManaChanged);

    bool bFound = false;
    const float TempCurrentHealth = InASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetHealthAttribute(), bFound);
    CurrentHealth = bFound ? TempCurrentHealth : 0.0f;

    bFound = false;
    const float TempMaxHealth = InASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetMaxHealthAttribute(), bFound);
    MaxHealth = bFound ? TempMaxHealth : 100.0f;

    bFound = false;
    const float TempCurrentMana = InASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetManaAttribute(), bFound);
    CurrentMana = bFound ? TempCurrentMana : 0.0f;

    bFound = false;
    const float TempMaxMana = InASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetMaxManaAttribute(), bFound);
    MaxMana = bFound ? TempMaxMana : 100.0f;

    UpdateHealthUI(CurrentHealth, MaxHealth);
    UpdateManaUI(CurrentMana, MaxMana);
}

void UPlayerStatWidget::UpdateHealthUI(float InCurrent, float InMax)
{
    if (HealthProgressBar)
    {
        const float Percent = FMath::IsNearlyZero(InMax) ? 0.0f : FMath::Clamp(InCurrent / InMax, 0.0f, 1.0f);
        HealthProgressBar->SetPercent(Percent);
    }
    if (HealthText)
    {
        HealthText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), InCurrent, InMax)));
    }
}

void UPlayerStatWidget::UpdateManaUI(float InCurrent, float InMax)
{
    if (ManaProgressBar)
    {
        const float Percent = FMath::IsNearlyZero(InMax) ? 0.0f : FMath::Clamp(InCurrent / InMax, 0.0f, 1.0f);
        ManaProgressBar->SetPercent(Percent);
    }
    if (ManaText)
    {
        ManaText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), InCurrent, InMax)));
    }
}

void UPlayerStatWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    CurrentHealth = Data.NewValue;
    UpdateHealthUI(CurrentHealth, MaxHealth);
}

void UPlayerStatWidget::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
    MaxHealth = Data.NewValue;
    UpdateHealthUI(CurrentHealth, MaxHealth);
}

void UPlayerStatWidget::OnManaChanged(const FOnAttributeChangeData& Data)
{
    CurrentMana = Data.NewValue;
    UpdateManaUI(CurrentMana, MaxMana);
}

void UPlayerStatWidget::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
    MaxMana = Data.NewValue;
    UpdateManaUI(CurrentMana, MaxMana);
}
