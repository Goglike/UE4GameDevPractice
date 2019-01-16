// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController() {
	
}

void AMainPlayerController::BeginPlay() {
	APlayerController::BeginPlay();
	this->ControlledCharacter = static_cast<AMainCharacter*>(this->GetPawn());
	if (this->ControlledCharacter == nullptr) {
		this->ClientMessage("Controlled Character is not defined");
	}
	else {
		ClientMessage("Controlled character posessed");
	}
	this->bShowMouseCursor = 1;
}

void AMainPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	APlayerController::SetupInputComponent();

	this->InputComponent->BindAxis("MoveForward", this, &AMainPlayerController::MoveForward);
	this->InputComponent->BindAxis("MoveRight", this, &AMainPlayerController::MoveRight);
	this->InputComponent->BindAction("CameraCloser", IE_Pressed, this, &AMainPlayerController::CameraCloser);
	this->InputComponent->BindAction("CameraFurther", IE_Pressed, this, &AMainPlayerController::CameraFurther);
	this->InputComponent->BindAction("CameraUp", IE_Pressed, this, &AMainPlayerController::CameraUp);
	this->InputComponent->BindAction("CameraDown", IE_Pressed, this, &AMainPlayerController::CameraDown);
	this->InputComponent->BindAction("CameraLeft", IE_Pressed, this, &AMainPlayerController::CameraLeft);
	this->InputComponent->BindAction("CameraRight", IE_Pressed, this, &AMainPlayerController::CameraRight);
	this->InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerController::Jump);
	//this->InputComponent->BindAction("ShieldBash", IE_Pressed, this, &AMainPlayerController::ShieldBash);
	this->InputComponent->BindAction("Test", IE_Pressed, this, &AMainPlayerController::Test);
}


void AMainPlayerController::PlayerTick(float DeltaTime) {
	APlayerController::PlayerTick(DeltaTime);
	FRotator CurrentRot;
//	float p, y, r;
	/*if (this->ControlledCharacter != nullptr) {
		CurrentRot = this->ControlledCharacter->GetActorRotation()+FRotator(0.0f,100.f,0.f);
		p = CurrentRot.Pitch;
		y = CurrentRot.Yaw;
		r = CurrentRot.Roll;
		this->ClientMessage(FString::SanitizeFloat(p) + " " + FString::SanitizeFloat(y) + " " + FString::SanitizeFloat(r));
	}*/
}

void AMainPlayerController::MoveForward(float AxisValue) {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->mvf = AxisValue;
	}
}

void AMainPlayerController::MoveRight(float AxisValue) {
	if (this->ControlledCharacter != nullptr) {
		//this->ControlledCharacter->MoveRight(AxisValue);
		this->ControlledCharacter->mvr = AxisValue;
	}
}

void AMainPlayerController::CameraCloser() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->CameraCloser();
		this->ClientMessage("CameraCloser");
	}
}

void AMainPlayerController::CameraFurther() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->CameraFurther();
		this->ClientMessage("CameraFurther");
	}
}

void AMainPlayerController::CameraUp() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->CameraUp();
		this->ClientMessage("CameraUp");
	}
}

void AMainPlayerController::CameraDown() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->CameraDown();
		this->ClientMessage("CameraDown");
	}
}

void AMainPlayerController::CameraLeft() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->CameraLeft();
		this->ClientMessage("CameraLeft");
		//this->ControlledCharacter->SetActorRelativeRotation(FRotator(0.0f, 100.0f, 0.0f));
		//this->SetControlRotation(this->GetControlRotation()+FRotator(0.0f,-10.f,0.0f));
		//this->ClientMessage("CameraLeft");
	}
}

void AMainPlayerController::CameraRight() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->CameraRight();
		this->ClientMessage("CamerRight");
	}
}

void AMainPlayerController::Jump() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->Jump();
	}
}

/*void AMainPlayerController::ShieldBash() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->ShieldBash();
	}
}*/

void AMainPlayerController::Test() {
	if (this->ControlledCharacter != nullptr) {
		this->ControlledCharacter->SetRagdolled();
	}
}