// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Controllable.generated.h"

UCLASS()
class KESG_API AControllable : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AControllable(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual	void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	AController* controller_;
};

using Controllable = AControllable;