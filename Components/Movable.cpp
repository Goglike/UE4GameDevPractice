// Fill out your copyright notice in the Description page of Project Settings.

#include "Movable.h"

#include "Components/ShapeComponent.h"

#include "Navigation/PathFollowingComponent.h"

#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"

UMovable::UMovable(const FObjectInitializer& ObjectInitializer) : UPawnMovementComponent(ObjectInitializer)
{
	this->ComponentTags.Add(FName(TEXT("Movement")));
	
	this->velocity = 150.0f;
	
	this->NavAgentProps.AgentHeight     = 40.0f;
	this->NavAgentProps.AgentRadius     = 40.0f;
	//this->NavAgentProps.AgentStepHeight = 0.5f;

	this->NavAgentProps.bCanWalk = this->MovementState.bCanWalk = true;	
	this->NavAgentProps.bCanFly = this->MovementState.bCanFly = false;
	this->NavAgentProps.bCanJump = this->MovementState.bCanJump = false;
	this->NavAgentProps.bCanSwim = this->MovementState.bCanSwim = false;
	this->NavAgentProps.bCanCrouch = this->MovementState.bCanCrouch = false;

	this->RegisterAllComponentTickFunctions(true);
}

void UMovable::BeginPlay()
{
	UPawnMovementComponent::BeginPlay();	
}

void UMovable::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UPawnMovementComponent::EndPlay(EndPlayReason);	
}

void UMovable::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	UPawnMovementComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//this->FollowPath(this->PathFollowingComp.Get(), DeltaTime);
	bool lol = false;
	
	if (this->PathFollowingComp.Get()->GetPath().Get())
	{
		this->PathFollowingComp.Get()->RegisterComponentWithWorld(this->GetWorld());
		this->PathFollowingComp.Get()->RegisterAllComponentTickFunctions(true);
		this->PathFollowingComp.Get()->SetComponentTickEnabled(true);
		
		if (this->PathFollowingComp.Get()->GetStatus() == EPathFollowingStatus::Moving)
		{
			
		}
	}
	
	// Make sure that everything is still valid, and that we are allowed to move.
	if (this->GetOwner() && this->UpdatedComponent && !this->ShouldSkipUpdate(DeltaTime))
	{
		if (this->PathFollowingComp.Get()->GetStatus() == EPathFollowingStatus::Moving)
		{
			this->GetWorld()->GetFirstPlayerController()->ClientMessage(FString::Printf(
				TEXT("%12.6f %12.6f %12.6f"),
				this->Velocity.GetClampedToMaxSize(1.0f).X,
				this->Velocity.GetClampedToMaxSize(1.0f).Y,
				this->Velocity.GetClampedToMaxSize(1.0f).Z
			));

			FVector vector = this->Velocity.GetClampedToMaxSize(1.0f) * this->velocity * DeltaTime;

			if (!vector.IsNearlyZero())
			{
				FHitResult hit_result;

				this->SafeMoveUpdatedComponent(vector, this->UpdatedComponent->GetComponentRotation(), true, hit_result);

				// If we bumped into something, try to slide along it
				if (hit_result.IsValidBlockingHit())
				{
					//this->SlideAlongSurface(vector, 1.f - hit_result.Time, hit_result.Normal, hit_result);
				}
			}
		}
	}
	
}

void UMovable::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	UPawnMovementComponent::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

	
	
}