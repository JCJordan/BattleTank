// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
	ATank* ControlledTank;
	void AimAtCrossHair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetCrossHairTargetLocation(FVector& TargetLocation) const;

	// The range the tank can see.
	UPROPERTY(EditDefaultsOnly)
	float CrossHairRange = 1000000; //In Cm

	// The X location of the Crosshair on the screen in fraction of viewport.
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	// The Y location of the Crosshair on the screen in fraction of viewport.
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	
};
