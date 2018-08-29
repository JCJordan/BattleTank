// Copyright FairgroundPandaStudio
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Holds Barrel details such as Max Elevation
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	void Elevate(float DegreesPerSecond);

private:

	// Max Degress the barrel can move each second
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegressPerSecond = 10;

	// Max Elevation of the barrel in degrees
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 40; 

	// Min Elevation of the barrel in degrees
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0; 
	
};
