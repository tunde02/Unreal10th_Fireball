// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GASCharacter.generated.h"

UCLASS()
class UNREAL10TH_FIREBALL_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AGASCharacter();

    UAbilitySystemComponent* GetAbilitySystemComponent() const { return ASC; }

protected:
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;

protected:
    TObjectPtr<UAbilitySystemComponent> ASC;

};
