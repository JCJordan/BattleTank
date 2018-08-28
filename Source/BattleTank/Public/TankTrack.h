// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

// Holds Track details such as throttle speed
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Sets throttle between -1 and 1.
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);
	
	// Set max driving force that throttle can cause.
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40000000; // 40 ton tank (kg) * 100000g acceleration (1000000m/s)
	
};
