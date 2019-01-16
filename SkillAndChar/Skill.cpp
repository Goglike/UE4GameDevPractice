// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill.h"


// Sets default values for this component's properties
USkill::USkill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkill::BeginPlay()
{
	Super::BeginPlay();
	//setting up flags to correspond to skill properties
	if (this->CastTime == 0.0f) { this->bHasCastTime = false; }
	if (this->Cooldown == 0.0f) { this->bHasCD = false; }
	// ...
	
}


// Called every frame
void USkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Safety. If skill does not possess cast time, nevertheless is casting - nothing happens
	if (this->bCurrentlyCasting && !this->bHasCastTime) { return; }

	

	if (CurrentCooldown > 0.0f) {
		CurrentCooldown -= DeltaTime;
	}
	if (CurrentCooldown <= 0.0f) {
		CurrentCooldown = 0.0f;
	}

	// ...
}

void USkill::SkillUse() {
	if (this->bCurrentlyCasting) { return; }
	else if (!this->bCurrentlyCasting && this)	{this->bCurrentlyCasting = true;}
}