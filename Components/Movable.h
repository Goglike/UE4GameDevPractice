// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PawnMovementComponent.h"

#include "Movable.generated.h"

UCLASS()
class KESG_API UMovable : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	UMovable(const FObjectInitializer & ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:	
	float velocity;
};

using Movable = UMovable;