// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	AActor* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Possessed Actor: %s"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Possessed Actor!"))
	}

}

ATank* ATankAIController::GetControlledTank() const {

	return dynamic_cast<ATank*>(GetPawn());
}


