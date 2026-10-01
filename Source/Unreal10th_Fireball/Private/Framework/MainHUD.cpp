// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainHUD.h"
#include "Widget/MainWidget.h"

#include "AbilitySystemInterface.h"

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!MainWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AMainHUD::BeginPlay()] : MainWidgetClass가 설정되지 않았습니다."));
        return;
    }

    APlayerController* PC = GetOwningPlayerController();
    if (!PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AMainHUD::BeginPlay()] : PlayerController가 nullptr입니다."));
        return;
    }

    MainWidgetInstance = CreateWidget<UMainWidget>(PC, MainWidgetClass);

    if (MainWidgetInstance)
    {
        MainWidgetInstance->AddToViewport();

        if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(PC->GetPawn()))
        {
            MainWidgetInstance->BindToASC(ASI->GetAbilitySystemComponent());
        }
    }
}
