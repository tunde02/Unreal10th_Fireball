// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASEnemyCharacter.h"
#include "GAS/AttributeSet/EnemyAttributeSet.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
    EnemyAttribute = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("Stat"));
}
