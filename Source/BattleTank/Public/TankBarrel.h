// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Holds Barrel details such as Max Elevation
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	void Elevate(float DegreesPerSecond);

private:

	// Max Degress the barrel can move each second
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegressPerSecond = 20;

	// Max Elevation of the barrel in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40; 

	// Min Elevation of the barrel in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0; 
	
};
