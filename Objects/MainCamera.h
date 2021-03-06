// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CameraMovementComponent.h"
#include "Engine/Engine.h"
#include "MainCamera.generated.h"


UCLASS()
class KESG_API AMainCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//UCameraMovementComponent* GetCameraMovement();

	UCameraComponent* Camera;
	UCameraMovementComponent* CameraMovement;

	
	
};
