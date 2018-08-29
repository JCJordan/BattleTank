// Copyright FairgroundPandaStudio

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Engine/StaticMeshSocket.h"
#include "UObject/UObjectGlobals.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	if (!TankAimingComponent) { UE_LOG(LogTemp, Error, TEXT("No Aiming Component on Tank!")); return; }
	if (!TankMovementComponent) { UE_LOG(LogTemp, Error, TEXT("No Movement Component on Tank!")); return; }
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector TargetLocation) const {
	TankAimingComponent->AimAt(TargetLocation, InitialProjectileSpeed);
	return;
}

void ATank::Fire() {

	if (!Barrel || !ProjectileBlueprint) { return; }

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	if (isReloaded) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(InitialProjectileSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}

	return;
}
