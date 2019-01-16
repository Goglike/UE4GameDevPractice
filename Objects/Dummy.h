// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Objects/Controllable.h"

#include "Components/Movable.h"
#include "Components/Selectable.h"

#include "Dummy.generated.h"

UCLASS()
class KESG_API ADummy : public AControllable
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ADummy(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	struct {
		Movable*    movable;
		Selectable* selectable;
	} component_;
};

using Dummy = ADummy;
