// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MainMode.generated.h"

UCLASS()
class KESG_API AMainMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainMode();
protected:
	virtual void BeginPlay() override;
	
};

using MainMode = AMainMode;