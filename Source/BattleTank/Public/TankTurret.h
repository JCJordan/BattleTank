// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

// Holds Turret details such as max yaw
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Turn(float DegreesPerSecond);

private:

	// Max Degress the turret can move each second
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegressPerSecond = 20;

};
