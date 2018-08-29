// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	return;

}


void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw / 2);
	RightTrack->SetThrottle(Throw / 2);

	return;

}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw / 2);
	RightTrack->SetThrottle(Throw * -1 / 2);

	return;
}


