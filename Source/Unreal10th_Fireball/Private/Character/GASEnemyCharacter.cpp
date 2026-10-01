// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASEnemyCharacter.h"
#include "GAS/AttributeSet/EnemyAttributeSet.h"
#include "Widget/OverheadHealthWidget.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
    EnemyAttribute = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("Stat"));

    OverheadHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadHealthWidgetComponent"));
    OverheadHealthWidgetComponent->SetupAttachment(GetRootComponent());
    OverheadHealthWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    OverheadHealthWidgetComponent->SetDrawSize(FVector2D(300.0f, 50.0f));
    OverheadHealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
    OverheadHealthWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGASEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (OverheadHealthWidgetComponent)
    {
        if (UOverheadHealthWidget* Widget = Cast<UOverheadHealthWidget>(OverheadHealthWidgetComponent->GetUserWidgetObject()))
        {
            Widget->BindToASC(ASC);
        }
    }
}

void AGASEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bFaceCamera)
    {
        UpdateOverHeadWidgetRotation();
    }
}

void AGASEnemyCharacter::UpdateOverHeadWidgetRotation()
{
    if (!OverheadHealthWidgetComponent)
    {
        return;
    }

    if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
    {
        FRotator WidgetRotation = (-CameraManager->GetCameraRotation().Vector()).Rotation();

        if (bLockWidgetPitch)
        {
            WidgetRotation.Pitch = 0.0f;
        }

        if (bLockWidgetRoll)
        {
            WidgetRotation.Roll = 0.0f;
        }

        OverheadHealthWidgetComponent->SetWorldRotation(WidgetRotation);
    }
}
