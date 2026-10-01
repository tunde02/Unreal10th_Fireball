// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/GASPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

void AGASPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (DefaultMappingContext)
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AGASPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (JumpAction)
        {
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AGASPlayerController::Jump);
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGASPlayerController::StopJumping);
        }

        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGASPlayerController::Move);
        }

        if (LookAction)
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGASPlayerController::Look);
        }
    }
}

void AGASPlayerController::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn())
    {
        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AGASPlayerController::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddYawInput(LookAxisVector.X);
    AddPitchInput(-LookAxisVector.Y);
}

void AGASPlayerController::Jump()
{
    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        ControlledCharacter->Jump();
    }
}

void AGASPlayerController::StopJumping()
{
    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        ControlledCharacter->StopJumping();
    }
}
