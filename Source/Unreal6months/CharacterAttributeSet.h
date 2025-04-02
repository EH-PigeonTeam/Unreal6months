// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class UNREAL6MONTHS_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


	UPROPERTY()
	FGameplayAttributeData Health = 100.0f;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health)



		UPROPERTY()
	FGameplayAttributeData Armor = 100.0f;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Armor)

		virtual void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override {
		Super::PreAttributeChange(Attribute, NewValue);

		if (Attribute == GetHealthAttribute())
		{
			UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
			const float CurrentHealthValue = Health.GetBaseValue();

			NewValue = FMath::Clamp(NewValue, 0.0f, 100);

			if (!FMath::IsNearlyEqual(CurrentHealthValue, NewValue)) {
				AbilityComp->ApplyModToAttributeUnsafe(Attribute, EGameplayModOp::Override, NewValue);
			}
		}
	}
};
