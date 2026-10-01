// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OverheadHealthWidget.h"
#include "GAS/AttributeSet/EnemyAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UOverheadHealthWidget::BindToASC(UAbilitySystemComponent* InASC)
{
    if (!InASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[UOverheadHealthWidget::BindToASC()] : ASC가 nullptr입니다."));
        return;
    }

    InASC->GetGameplayAttributeValueChangeDelegate(
        UEnemyAttributeSet::GetHealthAttribute()).AddUObject(this, &UOverheadHealthWidget::OnHealthChanged);

    InASC->GetGameplayAttributeValueChangeDelegate(
        UEnemyAttributeSet::GetMaxHealthAttribute())
        .AddUObject(this, &UOverheadHealthWidget::OnMaxHealthChanged);

    bool bFound = false;
    const float TempCurrentHealth = InASC->GetGameplayAttributeValue(UEnemyAttributeSet::GetHealthAttribute(), bFound);
    CurrentHealth = bFound ? TempCurrentHealth : 0.0f;

    bFound = false;
    const float TempMaxHealth = InASC->GetGameplayAttributeValue(UEnemyAttributeSet::GetMaxHealthAttribute(), bFound);
    MaxHealth = bFound ? TempMaxHealth : 100.0f;

    UpdateHealthUI(CurrentHealth, MaxHealth);
}

void UOverheadHealthWidget::UpdateHealthUI(float InCurrent, float InMax)
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

void UOverheadHealthWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    CurrentHealth = Data.NewValue;
    UpdateHealthUI(CurrentHealth, MaxHealth);
}

void UOverheadHealthWidget::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
    MaxHealth = Data.NewValue;
    UpdateHealthUI(CurrentHealth, MaxHealth);
}
