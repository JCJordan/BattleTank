// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	AActor* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Possessed Actor: %s"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Possessed Actor!"))
	}

}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	AimAtCrossHair();

}

ATank* ATankPlayerController::GetControlledTank() const {

	return dynamic_cast<ATank*>(GetPawn());
}

void ATankPlayerController::AimAtCrossHair() {
	
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}	
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	
	FHitResult OutHit;
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	
	FVector TraceEnd;
	if (!GetCrossHairTargetLocation(TraceEnd)) { return false; }
	
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
	//UE_LOG(LogTemp, Warning, TEXT("CameraLocation: %s - CameraRotation: %s"), *CameraLocation.ToString(), *CameraRotation.ToString())

	TargetLocation = CameraLocation + (CameraRotation * CrossHairRange);

	return true;

}
