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
	
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire() const;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

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

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UTankBarrel* Barrel = nullptr;

};
