// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Ready,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Component used by Tank to manage aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTankAimingComponent();

	// Initialise Barrel and Turret References.
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	// Make the tank fire at it's current target location.
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Reload();

	int32 GetCurrentAmmoStock() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	int32 CurrentAmmoStock = 0;

private:

	// Initial launch speed of Projectile
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float InitialProjectileSpeed = 15000; // in cm/s (170000 is top real tank speed)

	// Time in seconds to reload barrel.
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0f; // In Seconds

	// Reference to Projectile Blueprint Actor
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	float LastFireTime = 0.0;

	// Max Ammo Tank can hold.
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 MaxAmmoCapacity = 3;

	FVector TargetAimDirection;

	void MoveBarrelTowards(FVector AimDirection);
	bool IsBarrelMoving();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
