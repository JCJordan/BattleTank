// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle) {

	UE_LOG(LogTemp, Warning, TEXT("%s: throttle set to: %f"), *GetName(), Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = dynamic_cast<UPrimitiveComponent*>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return;

}

