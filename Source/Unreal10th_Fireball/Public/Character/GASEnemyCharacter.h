// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacter.h"
#include "GASEnemyCharacter.generated.h"

class UEnemyAttributeSet;
class UWidgetComponent;

UCLASS()
class UNREAL10TH_FIREBALL_API AGASEnemyCharacter : public AGASCharacter
{
    GENERATED_BODY()

public:
    AGASEnemyCharacter();

    UEnemyAttributeSet* GetEnemyAttribute() const { return EnemyAttribute; }

private:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    void UpdateOverHeadWidgetRotation();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    TObjectPtr<UEnemyAttributeSet> EnemyAttribute;

    UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "UI|OverHead")
    TObjectPtr<UWidgetComponent> OverheadHealthWidgetComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|OverHead")
    bool bFaceCamera = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|OverHead")
    bool bLockWidgetPitch = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|OverHead")
    bool bLockWidgetRoll = true;

};
