// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/GameplayAbility_Fireball.h"
#include "GAS/AttributeSet/PlayerAttributeSet.h"
#include "Projectile/FireballProjectile.h"

#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "AbilitySystemGlobals.h"

UGameplayAbility_Fireball::UGameplayAbility_Fireball()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_Fireball::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
    if (!Character)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // 대미지 EffectSpec 생성
    FGameplayEffectSpecHandle DamageSpec = MakeOutgoingGameplayEffectSpec(FireballDamageEffectClass, GetAbilityLevel(Handle, ActorInfo));
    if (DamageSpec.IsValid())
    {
        // SetByCaller로 파이어볼 피격 대미지 설정
        DamageSpec.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("GAS.Data.Damage")), FireballDamage);
    }

    // 화상 EffectSpec 생성
    FGameplayEffectSpecHandle BurnSpec = MakeOutgoingGameplayEffectSpec(FireballBurnEffectClass, GetAbilityLevel(Handle, ActorInfo));
    if (BurnSpec.IsValid())
    {
        // SetByCaller로 화상 대미지 설정
        BurnSpec.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("GAS.Data.Damage")), BurnDamage);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = Character;
    SpawnParams.Instigator = Character;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // 파이어볼 투사체 스폰
    AFireballProjectile* Projectile = GetWorld()->SpawnActor<AFireballProjectile>(
        FireballProjectileClass,
        Character->GetMesh()->GetSocketLocation(FName("FireballSocket")),
        Character->GetActorRotation(),
        SpawnParams
    );

    // 파이어볼 투사체에 SourceASC, 대미지 EffectSpec, 화상 EffectSpec 전달
    Projectile->InitializeFireballProjectile(ActorInfo->AbilitySystemComponent.Get(), DamageSpec, BurnSpec);

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

bool UGameplayAbility_Fireball::CheckCost(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    UGameplayEffect* CostGE = GetCostGameplayEffect();
    if (!CostGE)
    {
        UE_LOG(LogTemp, Warning, TEXT("[UGameplayAbility_Fireball::CheckCost] : Cost GameplayEffect가 없습니다."));
        return true;
    }

    UAbilitySystemComponent* ASC = ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr;
    if (!ASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[UGameplayAbility_Fireball::CheckCost] : ASC가 nullptr입니다."));
        return true;
    }

    if (!ASC->HasAttributeSetForAttribute(UPlayerAttributeSet::GetManaAttribute())
        || !ASC->HasAttributeSetForAttribute(UPlayerAttributeSet::GetManaCostAttribute()))
    {
        UE_LOG(LogTemp, Warning, TEXT("[UGameplayAbility_Fireball::CheckCost] : 어트리뷰트에 Mana 데이터를 불러올 수 없습니다."));
        return false;
    }

    // 시전자의 현재 Mana값 가져오기
    const float CurrentMana = ASC->GetNumericAttribute(UPlayerAttributeSet::GetManaAttribute());

    // 필요 소모량을 알기 위해 Spec 생성 및 모디파이어 계산
    const FGameplayEffectContextHandle EffectContext = MakeEffectContext(Handle, ActorInfo);
    const float AbilityLevel = GetAbilityLevel(Handle, ActorInfo);
    FGameplayEffectSpec Spec(CostGE, EffectContext, AbilityLevel);
    Spec.CalculateModifierMagnitudes();

    // 현재 효과에서 ManaCost를 변경시키는 모디파이어를 전부 불러와서 적용 후 값 갱신
    float ManaCost = 0.0f;
    bool bFoundManaModifier = false;
    for (int32 ModIndex = 0; ModIndex < Spec.Modifiers.Num(); ModIndex++)
    {
        if (Spec.Def && Spec.Def->Modifiers.IsValidIndex(ModIndex))
        {
            const FGameplayModifierInfo& ModDef = Spec.Def->Modifiers[ModIndex];
            if (ModDef.Attribute == UPlayerAttributeSet::GetManaCostAttribute())
            {
                const FModifierSpec& ModSpec = Spec.Modifiers[ModIndex];
                ManaCost += ModSpec.GetEvaluatedMagnitude();
                bFoundManaModifier = true;
            }
        }
    }

    // 현재 효과에 ManaCost 관련 모디파이어가 없으면 원래 함수 실행
    if (!bFoundManaModifier)
    {
        return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);
    }

    if (ManaCost <= CurrentMana)
    {
        return true;
    }

    // 실패 원인인 코스트 부족 태그를 OptionalRelevantTags에 추가
    const FGameplayTag& CostTag = UAbilitySystemGlobals::Get().ActivateFailCostTag;
    if (OptionalRelevantTags && CostTag.IsValid())
    {
        OptionalRelevantTags->AddTag(CostTag);
    }

    return false;
}
