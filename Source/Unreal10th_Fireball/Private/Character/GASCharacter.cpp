// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacter.h"

#include "AbilitySystemComponent.h"

AGASCharacter::AGASCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void AGASCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AGASCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (IsValid(ASC))
    {
        ASC->InitAbilityActorInfo(this, this);
    }
}
