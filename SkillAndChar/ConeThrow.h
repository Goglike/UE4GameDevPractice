// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "MainCharacter.h"
#include "ConeThrow.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAME_API UConeThrow : public USkill
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Skills")
		void UseSkill();
	UPROPERTY(EditAnywhere)
		float AttackRange = 100.0f;
	UPROPERTY(EditAnywhere)
		float AttackCone = 60.0f;
	UPROPERTY(EditAnywhere)
		float Impulse = 100000.0f;
	UPROPERTY(EditAnywhere)
		float Damage = 10.0f;
	float CosineOfAttackCone;
	void BeginPlay();
	
};
