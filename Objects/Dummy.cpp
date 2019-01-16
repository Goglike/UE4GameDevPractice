// Fill out your copyright notice in the Description page of Project Settings.

#include "Dummy.h"

#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "Engine/StaticMesh.h"

#include "Navigation/PathFollowingComponent.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
ADummy::ADummy(const FObjectInitializer& ObjectInitializer) : AControllable(ObjectInitializer)
{	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.	
	
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	this->RootComponent = SphereVisual;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(1.0f));
		
		SphereVisual->SetSimulatePhysics(true);
		SphereVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		SphereVisual->SetCanEverAffectNavigation(false);
	}

	this->component_.movable    = CreateDefaultSubobject<Movable>(TEXT("Movable"));
	this->component_.selectable = CreateDefaultSubobject<Selectable>(TEXT("Selectable"));

	this->component_.movable->UpdatedComponent = this->RootComponent;
	this->component_.movable->MovementState.bCanWalk = true;
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Controllable::Tick(DeltaTime);
	
	if (this->component_.movable->PathFollowingComp.Get() && this->component_.movable->PathFollowingComp.Get()->GetStatus() == EPathFollowingStatus::Moving)
	{
	//	static_cast<UStaticMeshComponent*>(this->RootComponent)->SetSimulatePhysics(false);
	}
	else
	{
		//static_cast<UStaticMeshComponent*>(this->RootComponent)->SetSimulatePhysics(true);
	}
}

UPawnMovementComponent* ADummy::GetMovementComponent() const
{
	return this->component_.movable;
}

void ADummy::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	Controllable::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Controllable::BeginPlay();
}
