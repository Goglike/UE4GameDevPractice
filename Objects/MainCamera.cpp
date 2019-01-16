// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCamera.h"


// Sets default values
AMainCamera::AMainCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
	UCameraMovementComponent* CameraMovement = CreateDefaultSubobject<UCameraMovementComponent>(TEXT("MovementComponent"));
	CameraMovement->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	APawn::BeginPlay();
	
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	APawn::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);
}

/*UCameraMovementComponent* AMainCamera::GetCameraMovement()
{
	if (this->CameraMovement) {
		return this->CameraMovement;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NIHUIA"));
	}
}*/

