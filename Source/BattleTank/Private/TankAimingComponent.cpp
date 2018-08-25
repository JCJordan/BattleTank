// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float InitialProjectileSpeed) {

	if (!Barrel) { return; }
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bVelocitySuggested;
	bVelocitySuggested = UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, TargetLocation, InitialProjectileSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bVelocitySuggested) {
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s with speed - %f gives aim: %s"), *(GetOwner()->GetName()), *TargetLocation.ToString(), InitialProjectileSpeed, *AimDirection.ToString());
	}
	return;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetAimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetAimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Turn(DeltaRotation.Yaw);

}
