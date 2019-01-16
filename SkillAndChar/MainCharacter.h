// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

#include "MainCharacter.generated.h"


UCLASS()
class GAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//some general properties
	UPROPERTY(EditAnywhere)
		float anus = 100.0f;
	UPROPERTY(EditAnywhere)
		float MeleeAttackRange = 40000.0f;
	UPROPERTY(EditAnywhere)
		float ConeOfAttack = 60.0f;
	UPROPERTY(EditAnywhere)
		float MeleeAttackZRange = 100.0f;

	//camera tweaks
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraCloser();
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraFurther();
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraUp();
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraDown();
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraLeft();
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraRight();
	float CurrentCameraAngle = 0.0f;

	//movement
	UFUNCTION(BlueprintCallable, Category = "CharacterFind")
		void MoveAlongDirection(FVector direction);
	int mvf = 0;
	int mvr = 0;

	//Health and damage system
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="HP")
		float HealthPoints = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="HP")
		float MaxHealthPoints = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HP")
		bool isDead=false;
	float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser
	);
	UFUNCTION(BlueprintCallable, Category = "HP")
		void Death();


	//innercooldowns, todo
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Semaphore")
		bool cppisAttacking = false;
	float AttackTime = 0.6f, currentAttackTime = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Semaphore")
		float GCD;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Semaphore")
		bool GCDflag = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Semaphore")
		FString GCDReason = TEXT("nogcd");

	//control over chatacter ragdoll
	bool IsRagdolled = false;
	float RagdollTime = 0.0f;
	UFUNCTION(BlueprintCallable, Category = "CharacterFind")
		void SetRagdolled();
	UFUNCTION(BlueprintCallable, Category = "CharacterFind")
		void SetNotRagdolled();
	

	//Miscelaneous
	USkeletalMeshComponent* Skeleton = nullptr;
	USpringArmComponent* SpringArm = nullptr;
	FTransform DefaultSkeletonTransform;
	void DecreaseGCD(float DeltaTime);
	void StartGCD(float time,FString reason);
};
