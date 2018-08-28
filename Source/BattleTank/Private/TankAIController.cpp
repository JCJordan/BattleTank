// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	ControlledTank = dynamic_cast<ATank*>(GetPawn());
	PlayerTank = dynamic_cast<ATank*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ControlledTank) { UE_LOG(LogTemp, Error, TEXT("Not possessing tank!")); }
	if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("Can't find player tank!")); }

}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	if (PlayerTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}

}


