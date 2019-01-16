// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API USkill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkill();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Cooldown
	UPROPERTY(EditAnywhere) float Cooldown = 5.0f;
	UPROPERTY(VisibleAnywhere) float CurrentCooldown = 0.0f;
	//deprecated with cast time
	UPROPERTY(EditAnywhere) float GlobalCooldown = 1.0f;
	
	//Cast time of the skill
	UPROPERTY(EditAnywhere)	float CastTime = 1.0f;
	UPROPERTY(VisibleAnywhere) float CurrentCastTime = 1.0f;
	
	//flags to easy understand skill properties
	UPROPERTY(VisibleAnywhere)	bool bCurrentlyCasting = false; // can ever became true only if skill has cast time
	UPROPERTY(VisibleAnywhere)	bool bCurrentlyOnCD = false;
	UPROPERTY(VisibleAnywhere)	bool bHasCastTime = true;
	UPROPERTY(VisibleAnywhere)	bool bHasCD = true;
	
	//SkillUsage
	virtual void SkillUse();

	//huerga
	UPROPERTY(EditAnywhere) FString reason = TEXT("nogcd");
	
};
