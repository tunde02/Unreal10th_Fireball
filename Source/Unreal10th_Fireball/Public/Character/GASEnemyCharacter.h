// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacter.h"
#include "GASEnemyCharacter.generated.h"

class UEnemyAttributeSet;

UCLASS()
class UNREAL10TH_FIREBALL_API AGASEnemyCharacter : public AGASCharacter
{
    GENERATED_BODY()

public:
    AGASEnemyCharacter();

    UEnemyAttributeSet* GetEnemyAttribute() const { return EnemyAttribute; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    TObjectPtr<UEnemyAttributeSet> EnemyAttribute;

};
