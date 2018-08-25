// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Turn(float RawDegreesPerSecond) {

	float DegreesPerSecond = FMath::Clamp<float>(RawDegreesPerSecond, MaxDegressPerSecond * -1, MaxDegressPerSecond);
	float YawChange = DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, NewYaw, 0));

	return;

}
