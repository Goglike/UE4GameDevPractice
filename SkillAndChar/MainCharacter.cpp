// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{	
	//searching for necessary components by name
	Super::BeginPlay();
	TArray<UActorComponent*> All;
	this->GetComponents(All);
	for (int i = 0; i < All.Num(); i++)
	{
		if (All[i])
		{
			UActorComponent* child = All[i];
			FString name = child->GetName();
			
			if (name == TEXT("SpringArm")) {
				SpringArm = Cast<USpringArmComponent>(All[i]);
			}
			
		}
	}
	//settingup spring arm
	if (SpringArm != nullptr) {
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	}

	//Get skeleton and its defaults for reattaching skeleton to capsule
	Skeleton = this->GetMesh();
	this->DefaultSkeletonTransform = Skeleton->GetRelativeTransform();

	//character movement component setup	
	this->GetCharacterMovement()->bOrientRotationToMovement=true;
	this->GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//testplayercontroller
	//GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, this->GCDReason);

	//Every tick taking movement from pressed buttons and camera direction and initiate it
	if (this->isDead) {
		return;
	}

	if (this->HealthPoints <= 0.0f) {
		this->Death();
		return;
	}
	
	if (this->GCDflag && this->GetMovementComponent()->IsFalling()) { 
		this->DecreaseGCD(DeltaTime);
		return; 
	}

	if (this->GCDflag && !(this->GetMovementComponent()->IsFalling())) { 
		this->GetCharacterMovement()->StopMovementImmediately();
		this->DecreaseGCD(DeltaTime);
		return;
	}

	if (((this->mvf != 0) || (this->mvr != 0)) && !this->IsRagdolled) {
		this->MoveAlongDirection(FVector(mvf, mvr, 0.f).RotateAngleAxis(CurrentCameraAngle, FVector(0.0f, 0.0f, 1.0f)));
		return;
	}

	//flag for when this character is attacking
	/*if (this->cppisAttacking) {
		this->GetCharacterMovement()->StopMovementImmediately();
		this->currentAttackTime += DeltaTime;
		if (this->currentAttackTime >= this->AttackTime) {
			this->cppisAttacking = false;
			this->currentAttackTime = 0.0f;
		}
	}*/

	//flag for when this character is ragdolled
	if (this->IsRagdolled) {
		//Moving capsule with skeleton
		FVector SkeletonLocation = this->Skeleton->GetRelativeTransform().GetTranslation();
		SkeletonLocation.Z += 200.0f;
		FVector DeepDown = SkeletonLocation;
		DeepDown.Z = SkeletonLocation.Z-1000.f;
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, SkeletonLocation, DeepDown, ECC_Visibility);
		this->GetRootComponent()->SetRelativeLocation(FVector(SkeletonLocation.X, SkeletonLocation.Y, Hit.Location.Z+this->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	    //character Gets up from ragdoll
		this->RagdollTime+= DeltaTime;
		if (this->RagdollTime >= 3.0f) {
			this->SetNotRagdolled();
			this->Skeleton->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			this->Skeleton->SetRelativeTransform(this->DefaultSkeletonTransform);
		}
	}

	//testing if its time to free this land for young
	
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMainCharacter::CameraCloser() {
	if (this->SpringArm != nullptr) {
		SpringArm->TargetArmLength = SpringArm->TargetArmLength / 1.5f;
	}
}

void AMainCharacter::CameraFurther() {
	if (this->SpringArm != nullptr) {
		SpringArm->TargetArmLength = SpringArm->TargetArmLength*1.5f;
	}
}

void AMainCharacter::CameraUp() {
	if (this->SpringArm != nullptr) {
		if (FRotator(SpringArm->GetRelativeTransform().GetRotation()).Pitch <= 75.f) {
			SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeTransform().GetRotation()) + FRotator(10.0f, 0.0f, 0.0f));
		}
	}
}

void AMainCharacter::CameraDown() {
	if (this->SpringArm != nullptr) {
		if (FRotator(SpringArm->GetRelativeTransform().GetRotation()).Pitch >= -75.f) {
			SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeTransform().GetRotation()) + FRotator(-10.0f, 0.0f, 0.0f));
		}
	}
}

void AMainCharacter::CameraLeft() {
	if (this->SpringArm != nullptr) {
		if (FRotator(SpringArm->GetRelativeTransform().GetRotation()).Pitch <= 75.f) {
			SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeTransform().GetRotation()) + FRotator(0.0f, -10.0f, 0.0f));
			CurrentCameraAngle -= 10.0f;
			if (CurrentCameraAngle < 0.0f) {
				CurrentCameraAngle += 360.0f;
			}
		}
	}
}

void AMainCharacter::CameraRight() {
	if (this->SpringArm != nullptr) {
		if (FRotator(SpringArm->GetRelativeTransform().GetRotation()).Pitch <= 75.f) {
			SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeTransform().GetRotation()) + FRotator(0.0f, 10.0f, 0.0f));
			CurrentCameraAngle += 10.0f;
			if (CurrentCameraAngle >= 360.0f) {
				CurrentCameraAngle -= 360.0f;
			}
		}
	}
}

void AMainCharacter::MoveAlongDirection(FVector direction) {
	AddMovementInput(direction, 1.0f);
}


void AMainCharacter::SetRagdolled() {
	this->Skeleton->SetSimulatePhysics(true);
	this->IsRagdolled = true;
}

void AMainCharacter::SetNotRagdolled() {
	this->Skeleton->SetSimulatePhysics(false);
	this->IsRagdolled = false;
	this->RagdollTime = 0.0f;
}

float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	this->HealthPoints -= DamageAmount;
	return DamageAmount;
}

void AMainCharacter::Death() {
	this->SetRagdolled();
	this->isDead = true;
	this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMainCharacter::DecreaseGCD(float Deltatime) {
	this->GCD -= Deltatime;
	if (this->GCD <= 0.0f) {
		this->GCDflag = false;
		this->GCD = 0.0f;
		this->GCDReason = TEXT("nogcd");
	}
}

void AMainCharacter::StartGCD(float time,FString reason) {
	this->GCD = time;
	this->GCDflag = true;
	this->GCDReason = reason;
}