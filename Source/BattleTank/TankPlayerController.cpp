// Copyright FairgroundPandaStudio

#include "TankPlayerController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	ControlledTank = dynamic_cast<ATank*>(GetPawn());
	if (!ensure(ControlledTank)) { UE_LOG(LogTemp, Error, TEXT("No controlled tank!"));  }
	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { FoundAimingComponent(AimingComponent); }
	else { UE_LOG(LogTemp, Error, TEXT("Aiming Component not found on controlled tank! (At BeginPlay)")) }
	

}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	AimAtCrossHair();

}

void ATankPlayerController::AimAtCrossHair() {
	
	if (!ensure(ControlledTank)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		ControlledTank->AimAt(HitLocation);
	}	
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	
	FHitResult OutHit;
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	
	FVector TraceEnd;
	if (!ensure(GetCrossHairTargetLocation(TraceEnd))) { return false; }
	
	bool bLineTraceFoundHit;
	bLineTraceFoundHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	
	if (bLineTraceFoundHit) { HitLocation = OutHit.Location; return true; }
	else { return false; }
	
}

bool ATankPlayerController::GetCrossHairTargetLocation(FVector& TargetLocation) const {

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D CrosshairScreenLocation{ ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation };

	FVector CameraLocation, CameraRotation;
	DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, CameraLocation, CameraRotation);

	TargetLocation = CameraLocation + (CameraRotation * CrossHairRange);

	return true;

}

ATank* ATankPlayerController::GetControlledTank() const {
	return ControlledTank;
}
