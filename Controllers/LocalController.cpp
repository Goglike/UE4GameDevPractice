// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalController.h"

#include "Controllers/AI.h"

#include "Objects/Controllable.h"

#include "Components/Movable.h"
#include "Components/Selectable.h"

#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"

ALocalController::ALocalController(const FObjectInitializer& ObjectInitializer) : APlayerController(ObjectInitializer)
{
	this->selected_ = nullptr;
	this->bShowMouseCursor = true;
}

void ALocalController::PlayerTick(float DeltaTime)
{
	APlayerController::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired

	//if (this->selected_ && this->selected_->GetComponentByClass(Movement::StaticClass()))
	//{
		//float distance = FVector::Dist(this->destination_, this->selected_->GetActorLocation());		

		// We need to issue move command only if far enough in order for walk animation to play correctly
		//if (this->GetWorld()->GetNavigationSystem() && (distance > 120.0f))
		//{
			//this->GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(static_cast<Controllable*>(this->selected_)->GetController(), this->destination_);
			//MyPawn->SetActorLocation(DestLocation);
		//}
	//}
}

void ALocalController::SetupInputComponent()
{
	// set up gameplay key bindings
	APlayerController::SetupInputComponent();
	
	//this->InputComponent->BindAction("Select", IE_Pressed, this, &ALocalController::OnSelectPressed);
	this->InputComponent->BindAction("Select", IE_Released, this, &ALocalController::OnSelectReleased);

	//this->InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALocalController::OnSetDestinationPressed);
	this->InputComponent->BindAction("SetDestination", IE_Released, this, &ALocalController::OnSetDestinationReleased);
}

void ALocalController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released	
}

void ALocalController::OnSetDestinationReleased()
{
	if (this->selected_)
	{
		FHitResult hit_result;

		auto movement_component = this->selected_->GetComponentByClass(Movable::StaticClass());

		if (movement_component)
		{
			this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_result);

			if (hit_result.bBlockingHit)
			{
				this->destination_ = hit_result.ImpactPoint;

				this->ClientMessage(FString::Printf(TEXT("Actor moving to: %f %f %f"),
					hit_result.ImpactPoint.X, hit_result.ImpactPoint.Y, hit_result.ImpactPoint.Z));

				APawn* pawn = static_cast<decltype(pawn)>(this->selected_);

				
				static_cast<AI*>(pawn->GetController())->MoveToLocation(hit_result.ImpactPoint);					
			}
		}
	}
}

void ALocalController::OnSelectPressed()
{
	
}

void ALocalController::OnSelectReleased()
{
	FHitResult hit_result;

	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_result);

	this->ClientMessage(TEXT("Select event"));

	if (hit_result.bBlockingHit && hit_result.GetActor() && hit_result.GetActor()->GetComponentByClass(Selectable::StaticClass()))
	{
		this->ClientMessage(FString::Printf(TEXT("Selected actor: %s"), *(hit_result.GetActor()->GetName())));
		
		this->selected_ = hit_result.GetActor();
	}
}
