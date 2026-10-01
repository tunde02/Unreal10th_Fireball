// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Widget/PlayerStatWidget.h"

void UMainWidget::BindToASC(UAbilitySystemComponent* InASC)
{
    if (!InASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[UMainWidget::BindToASC()] : ASC가 nullptr입니다."));
        return;
    }

    PlayerStatWidget->BindToASC(InASC);
}
