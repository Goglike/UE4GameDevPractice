// Fill out your copyright notice in the Description page of Project Settings.

#include "AI.h"

#include "Components/PathFinder.h"

AAI::AAI(const FObjectInitializer& ObjectInitializer) : AAIController(ObjectInitializer.SetDefaultSubobjectClass<PathFinder>(TEXT("PathFollowingComponent")))
{
	this->bAllowStrafe = true;
}

void AAI::BeginPlay()
{	
	AAIController::BeginPlay();

	
}
