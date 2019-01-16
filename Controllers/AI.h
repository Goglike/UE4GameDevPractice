// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AI.generated.h"

UCLASS()
class KESG_API AAI : public AAIController
{
	GENERATED_BODY()
public:
	AAI(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};

using AI = AAI;