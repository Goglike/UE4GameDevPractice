// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMode.h"

#include "Objects/Controllable.h"
#include "Controllers/LocalController.h"
#include "Objects/Dummy.h"

#include "UObject/UObjectGlobals.h"

#include "Engine/World.h"
#include "Engine/Level.h"

AMainMode::AMainMode()
{
	this->DefaultPlayerName = NSLOCTEXT("Player", "PlayerName", "Player");
	//this->DefaultPawnClass      = Dummy::StaticClass();
	this->PlayerControllerClass = LocalController::StaticClass();
}

void AMainMode::BeginPlay()
{
	auto controller = this->GetWorld()->GetFirstPlayerController();
	auto dummy = this->GetWorld()->SpawnActor<ADummy>(ADummy::StaticClass(), FVector(0, 0, 125), FRotator(EForceInit::ForceInitToZero));

	if (controller)
	{
		controller->ClientMessage(TEXT("Dummy created"));

		controller->GetPawn()->TeleportTo(FVector(0, 0, 1000), FRotator(EForceInit::ForceInitToZero));

		controller->ClientMessage(TEXT("Controller teleported"));		
	}	
}
