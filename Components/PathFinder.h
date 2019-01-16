// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Navigation/PathFollowingComponent.h"

#include "PathFinder.generated.h"

UCLASS()
class KESG_API UPathFinder : public UPathFollowingComponent
{
	GENERATED_BODY()
public:
	UPathFinder(const FObjectInitializer & ObjectInitializer);

private:
	float velocity;
};

using PathFinder = UPathFinder;