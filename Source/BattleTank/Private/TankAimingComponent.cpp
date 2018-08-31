// Copyright FairgroundPandaStudio

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

UTankAimingComponent::UTankAimingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;

	return;
}

void UTankAimingComponent::BeginPlay() {

	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTime) { FiringState = EFiringState::Reloading; }
	else if (IsBarrelMoving()) { FiringState = EFiringState::Aiming; }
	else { FiringState = EFiringState::Ready; }
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
	TargetAimDirection = AimDirection;
	FRotator TargetAimRotation = TargetAimDirection.Rotation();
	FRotator DeltaRotation = TargetAimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	// TODO is there a better way to do this?
	if (DeltaRotation.Yaw > 180) { DeltaRotation.Yaw = DeltaRotation.Yaw - 360; }
	else if (DeltaRotation.Yaw < -180) { DeltaRotation.Yaw = DeltaRotation.Yaw + 360; }
	Turret->Turn(DeltaRotation.Yaw);

	return;
}

bool UTankAimingComponent::IsBarrelMoving() {

	if (!ensure(Barrel)) { return false; }
	FVector CurrentBarrelDirection = Barrel->GetForwardVector();

	return !CurrentBarrelDirection.Equals(TargetAimDirection, 0.1f);
}

void UTankAimingComponent::Fire() {

	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	if (FiringState != EFiringState::Reloading) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(InitialProjectileSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}

	return;
}