// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UTankAimingComponent* TankAimingComponent = nullptr;
	void AimAt(FVector TargetLocation) const;

	// Set the Barrel Blueprint reference the tank will use
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Set the Turret Blueprint reference the barrel will use
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	// Make the tank fire at it's current target location.
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	// Initial launch speed of Projectile
	UPROPERTY(EditAnywhere, Category = Firing)
	float InitialProjectileSpeed = 15000; // in cm/s 

	// Time in seconds to reload barrel.
	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTime = 3.0f; // In Seconds

	// Reference to Projectile Blueprint Actor
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UTankBarrel* Barrel = nullptr;
	
	double LastFireTime = 0.0;

};
