// Copyright FairgroundPandaStudio

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;

	return;
}

void UTankAimingComponent::AimAt(FVector TargetLocation) {

	if (!ensure(Barrel && Turret)) { return; }
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bVelocitySuggested;
	bVelocitySuggested = UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, TargetLocation, InitialProjectileSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bVelocitySuggested) {
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetAimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetAimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Turn(DeltaRotation.Yaw);

	return;
}

void UTankAimingComponent::Fire() {

	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	if (isReloaded) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(InitialProjectileSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}

	return;
}