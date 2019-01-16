// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UEffect : public UObject
{
	GENERATED_BODY()

public:
	UEffect();
	virtual void LaunchEffect();
	virtual void Remove();
	//TBD. amount for some reason cannot be static
	 int amount;
	int ID;
	// Actors who applied effect and current actor which posesses it.
	TWeakPtr<AActor> applied;
	TWeakPtr<AActor> possesed;
	//effect duration
	
	int duration;
	FString name;


};
