// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "LocalController.generated.h"

UCLASS()
class KESG_API ALocalController : public APlayerController
{
	GENERATED_BODY()
public:
	ALocalController(const FObjectInitializer& ObjectInitializer);
private:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void OnSelectPressed();
	void OnSelectReleased();

	AActor* selected_;

	FVector destination_;
};

using LocalController = ALocalController;