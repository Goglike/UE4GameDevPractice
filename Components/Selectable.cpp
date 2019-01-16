// Fill out your copyright notice in the Description page of Project Settings.

#include "Selectable.h"


// Sets default values for this component's properties
USelectable::USelectable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->ComponentTags.Add(FName(TEXT("Selectable")));

	// ...
}


// Called when the game starts
void USelectable::BeginPlay()
{
	USceneComponent::BeginPlay();

	// ...
	
}


// Called every frame
void USelectable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	USceneComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

