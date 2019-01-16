// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllable.h"

#include "Controllers/AI.h"

// Sets default values
AControllable::AControllable(const FObjectInitializer& ObjectInitializer) : APawn(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->controller_ = this->CreateDefaultSubobject<AI>(TEXT("Controller"));	
}

// Called when the game starts or when spawned
void AControllable::BeginPlay()
{
	APawn::BeginPlay();

	this->controller_->Possess(this);
	
}

// Called every frame
void AControllable::Tick(float DeltaTime)
{
	APawn::Tick(DeltaTime);

}

// Called to bind functionality to input
void AControllable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);
}

void AControllable::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	APawn::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

