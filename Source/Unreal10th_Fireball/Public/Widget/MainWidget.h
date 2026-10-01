// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UAbilitySystemComponent;
class UPlayerStatWidget;

UCLASS()
class UNREAL10TH_FIREBALL_API UMainWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void BindToASC(UAbilitySystemComponent* InASC);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UPlayerStatWidget> PlayerStatWidget;

};
