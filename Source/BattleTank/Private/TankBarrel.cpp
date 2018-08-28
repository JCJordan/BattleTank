// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RawDegreesPerSecond) {

	float DegreesPerSecond = FMath::Clamp<float>(RawDegreesPerSecond, MaxDegressPerSecond * -1, MaxDegressPerSecond);
	float ElevationChange = DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float NewElevation;

	NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewElevation, 0, 0));

	return;

}
