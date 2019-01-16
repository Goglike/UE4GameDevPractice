// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraController.h"
#include <string>
#include <cmath> 


void AMainCameraController::PlayerTick(float DeltaTime)
{
	float mouseX;
	float mouseY;
	float sizeX;
	float sizeY;
	this->xAxis = 0.0f;
	this->yAxis = 0.0f;
	APlayerController::PlayerTick(DeltaTime);
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	this->GetMousePosition(mouseX, mouseY);
	sizeX = ViewportSize.X;
	sizeY = ViewportSize.Y;
	if (!isRotateButtonPressed) {
		if (mouseX < 10.0) {
			yAxis = -1.0f;
		}
		if (mouseX > (sizeX - 10.0)) {
			yAxis = 1.0f;
		}
		if (mouseY < 10.0) {
			xAxis = 1.0f;
		}
		if (mouseY > (sizeY - 10.0)) {
			xAxis = -1.0f;
		}
		this->MoveInDirection(this->CalculateMovenentInThisFrame(DeltaTime));
	}
	

	

	// keep updating the destination every tick while desired
	
}

void AMainCameraController::BeginPlay() {
	APlayerController::BeginPlay();
	this->bShowMouseCursor = true;
	DefaultCameraHeight = 100.0f;
	CameraSpeed = 100.0f;
	this->GetPawn()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	isRotateButtonPressed = false;
	CameraRotateSpeed = 1.0f;
}

void AMainCameraController::SetupInputComponent()
{
	// set up gameplay key bindings
	APlayerController::SetupInputComponent();

	this->InputComponent->BindAxis("MoveForward", this, &AMainCameraController::MoveForward);
	this->InputComponent->BindAxis("MoveRight", this, &AMainCameraController::MoveRight);
	this->InputComponent->BindAxis("MouseX", this, &AMainCameraController::RotateX);
	this->InputComponent->BindAxis("MouseY", this, &AMainCameraController::RotateY);
	this->InputComponent->BindAxis("MoveRight", this, &AMainCameraController::MoveRight);
	this->InputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &AMainCameraController::ZoomOut);
	this->InputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &AMainCameraController::ZoomIn);
	this->InputComponent->BindAction("FreeRotate", IE_Pressed, this, &AMainCameraController::FreeRotatePressed);
	this->InputComponent->BindAction("FreeRotate", IE_Released, this, &AMainCameraController::FreeRotateReleased);
}

void AMainCameraController::MoveForward(float AxisValue)
{	
	this->xAxis = AxisValue;
}

void AMainCameraController::MoveRight(float AxisValue)
{
	this->yAxis = AxisValue;
}

void AMainCameraController::MoveInDirection(FVector Direction) {
	APawn* const Cam = this->GetPawn();
	UPawnMovementComponent* movecam = Cam->GetMovementComponent();
	if (movecam)
	{
		movecam->AddInputVector(Direction);
	}
}

FVector AMainCameraController::CalculateMovenentInThisFrame(float DeltaTime) {
	FVector direction,tempForward,tempRight;
	
	tempForward = this->GetPawn()->GetActorForwardVector();
	tempForward.Z = 0;
	tempForward= tempForward.GetClampedToMaxSize(1.0f)*this->xAxis;

	tempRight = this->GetPawn()->GetActorRightVector();
	tempRight.Z = 0;
	tempRight=tempRight.GetClampedToMaxSize(1.0f)*this->yAxis;

	direction = tempForward + tempRight;
	direction = direction.GetClampedToMaxSize(1.0f)*CameraSpeed*DeltaTime;
	direction.Z = DefaultCameraHeight - this->CheckHeight();
	//if (direction.Size() > 500.f) {
		//return FVector(0.0f,0.0f,0.0f);
	//}
	//else {
		return direction;
	//}
}

float AMainCameraController::CheckHeight()
{
	APawn* const Cam = this->GetPawn();
	FVector Pos = Cam->GetActorLocation();
	FVector XYPosUnderground = FVector(Pos.X, Pos.Y, -10000.0f);
	FVector ImpactPoint;
	FHitResult hit_result;
	GetWorld()->LineTraceSingleByChannel(hit_result, Pos, XYPosUnderground, ECC_Visibility);
	
	if (hit_result.bBlockingHit)
	{
		ImpactPoint = hit_result.ImpactPoint;
		return  Pos.Z - ImpactPoint.Z;
	}
	else {
		return 0.0f;
	}

}

void AMainCameraController::ZoomOut() {
	float CurrentYaw=this->GetPawn()->GetActorRotation().Yaw;
	if (this->DefaultCameraHeight <= 2000.0f) {
		this->DefaultCameraHeight = std::pow(2.0f, (std::log2(this->DefaultCameraHeight / 100.0f) + 1.0f))*100.f;
		this->ClientMessage(FString::SanitizeFloat(this->DefaultCameraHeight));
		this->GetPawn()->SetActorRotation(FRotator(-(10+10*(std::log2(this->DefaultCameraHeight / 100.0f) + 1.0f)),CurrentYaw,0.0f));
		this->ClientMessage(FString::SanitizeFloat(-(10 + 10 * (std::log2(this->DefaultCameraHeight / 100.0f)))));
		this->CameraSpeed *= 2.0f;
	}	
}
void AMainCameraController::ZoomIn() {
	float CurrentYaw = this->GetPawn()->GetActorRotation().Yaw;
	if (this->DefaultCameraHeight >= 150.0f) {
		this->DefaultCameraHeight = std::pow(2.0f, (std::log2(this->DefaultCameraHeight / 100.0f) - 1.0f))*100.f;;
		this->ClientMessage(FString::SanitizeFloat(this->DefaultCameraHeight));
		this->GetPawn()->SetActorRotation(FRotator(-(10 + 10 * (std::log2(this->DefaultCameraHeight / 100.0f))), CurrentYaw, 0.0f));
		this->CameraSpeed *= 0.5f;
	}
}

void AMainCameraController::FreeRotatePressed() {
	this->bShowMouseCursor = false;
	this->isRotateButtonPressed = true;
}
void AMainCameraController::FreeRotateReleased() {
	this->bShowMouseCursor = true;
	this->isRotateButtonPressed = false;
}

void AMainCameraController::RotateX(float AxisValue) {
	APawn* Cam = this->GetPawn();
	if (this->isRotateButtonPressed && Cam) {
		FRotator NewRotation = Cam->GetActorRotation();
		NewRotation.Yaw += AxisValue*this->CameraRotateSpeed;
		Cam->SetActorRotation(NewRotation);
	}
}

void AMainCameraController::RotateY(float AxisValue) {
	APawn* Cam = this->GetPawn();
	if (this->isRotateButtonPressed && Cam) {
		FRotator NewRotation = Cam->GetActorRotation();
		NewRotation.Pitch += AxisValue*this->CameraRotateSpeed;
		if (NewRotation.Pitch < 85.0f && NewRotation.Pitch > -85.0f) {
			Cam->SetActorRotation(NewRotation);
		}
	}
}