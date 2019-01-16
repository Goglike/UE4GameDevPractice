// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "MainCharacter.h"
#include "DamageCone.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAME_API UDamageCone : public USkill
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Skills")
		void UseSkill();
	UPROPERTY(EditAnywhere)
		float AttackRange = 100.0f;
	UPROPERTY(EditAnywhere)
		float AttackCone = 60.0f;
	UPROPERTY(EditAnywhere)
		float Damage = 10.0f;
	UPROPERTY(VisibleAnywhere)
		float CosineOfAttackCone;
	void BeginPlay();
	
	
};
