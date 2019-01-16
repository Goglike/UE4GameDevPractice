// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Objects/MainCamera.h"
#include "Engine/Engine.h"
#include "MainCameraController.generated.h"

/**
 * 
 */
UCLASS()
class KESG_API AMainCameraController : public APlayerController
{
	GENERATED_BODY()
protected:
	float CheckHeight();
public:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	float DefaultCameraHeight;
	float const MinCameraHeight = 100.0f;
	float const MaxCameraHeight = 3200.0f;
	float CameraRotateSpeed;
	float CameraSpeed;
	float xAxis;
	float yAxis;
	float zAxis;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveInDirection(FVector Direction);
	void RotateX(float AxisValue);
	void RotateY(float AxisValue);
	void FreeRotatePressed();
	void FreeRotateReleased();
	bool isRotateButtonPressed;
	void ZoomOut();
	void ZoomIn();
	FVector CalculateMovenentInThisFrame(float DeltaTime);
};
