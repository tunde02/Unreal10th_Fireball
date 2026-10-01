// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacter.h"
#include "GASPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREAL10TH_FIREBALL_API AGASPlayerCharacter : public AGASCharacter
{
    GENERATED_BODY()

public:
    AGASPlayerCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    void CastFireball();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> IMC_Fireball;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> IA_Fireball;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    //TSubclassOf<UGameplayAbility> FireballAbilityClass;

    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (Clamp = "1"))
    //int32 FireballAbilityLevel = 1;

private:
    //UPROPERTY(Transient)
    //FGameplayAbilitySpecHandle FireballAbilitySpecHandle;

    //static constexpr int32 FireballInputId = 100;

};
