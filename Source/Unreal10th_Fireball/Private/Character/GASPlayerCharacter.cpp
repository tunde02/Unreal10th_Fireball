// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASPlayerCharacter.h"
#include "GAS/AttributeSet/PlayerAttributeSet.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AGASPlayerCharacter::AGASPlayerCharacter()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    PlayerAttribute = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("Stat"));

    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AGASPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Fireball Input Mapping Context 추가
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(IMC_Fireball, 0);
        }
    }
}

void AGASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (IA_Fireball)
        {
            EnhancedInputComp->BindAction(IA_Fireball, ETriggerEvent::Started, this, &AGASPlayerCharacter::CastFireball);
        }
    }
}

void AGASPlayerCharacter::CastFireball()
{
    UE_LOG(LogTemp, Log, TEXT("[AGASPlayerCharacter::CastFireball()] : Hello"));
}
