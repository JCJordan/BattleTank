// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

// Class for controlling tank as player.
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	APawn* ControlledTank;
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
	
	UFUNCTION()
	void OnPossessedTankDeath();

};
