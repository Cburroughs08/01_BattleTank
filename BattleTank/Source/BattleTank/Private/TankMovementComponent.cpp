// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftSet, UTankTrack* RightSet) {

	if (!LeftSet || !RightSet) { return; }

	LeftTrack = LeftSet;
	RightTrack = RightSet;


}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIFowardIntention = MoveVelocity.GetSafeNormal();
	auto FowardThrow = FVector::DotProduct(TankForward, AIFowardIntention);
	
	IntendMoveForward(FowardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIFowardIntention).Z;
	IntendTurnRight(RightThrow);
 }


void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}


void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}