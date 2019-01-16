// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainPlayerController();
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
private:
	AMainCharacter* ControlledCharacter=nullptr;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Jump();
	void CameraCloser();
	void CameraFurther();
	void CameraUp();
	void CameraDown();
	void CameraLeft();
	void CameraRight();
	//void ShieldBash();
	void Test();

};
