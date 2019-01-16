// Fill out your copyright notice in the Description page of Project Settings.

#include "ConeThrow.h"

void UConeThrow::BeginPlay() {
	Super::BeginPlay();
	this->CosineOfAttackCone = FMath::Cos(this->AttackCone);
}

void UConeThrow::UseSkill() {
	if (CurrentCooldown != 0.0f) {
		return;
	}
	AMainCharacter* that = Cast<AMainCharacter>(this->GetOwner());
	that->StartGCD(this->GlobalCooldown,this->reason);
	//getting actor which owns this component
	
	//starting cooldown
	this->CurrentCooldown = this->Cooldown;

	float x = that->GetActorLocation().X;
	float y = that->GetActorLocation().Y;
	float z = that->GetActorLocation().Z;
	FVector forward = that->GetActorForwardVector();

	for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
	{
		TWeakObjectPtr<APawn, FWeakObjectPtr> WeakPawn = *Iterator;
		APawn* Pawn = WeakPawn.Get();
		AMainCharacter* Character = Cast<AMainCharacter>(Pawn);
		if (Character != nullptr) {
			float tx = Character->GetActorLocation().X;
			float ty = Character->GetActorLocation().Y;
			float tz = Character->GetActorLocation().Z;
			if (((tx - x)*(tx - x) + (ty - y)*(ty - y) < this->AttackRange) && (Character != that) && (!Character->isDead)) {
				FVector temp = FVector(tx - x, ty - y, 0);
				if (FVector::DotProduct(forward.GetSafeNormal(), temp.GetSafeNormal()) > this->CosineOfAttackCone) {
					Character->SetRagdolled();
					Character->Skeleton->AddImpulse(this->Impulse*temp.GetSafeNormal(), TEXT("pelvis"));
					Character->TakeDamage(this->Damage, FDamageEvent::FDamageEvent(), that->GetController(), that);
				}
			}

		}

	}

}


