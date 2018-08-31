// Copyright FairgroundPandaStudio

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/NavMovementComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	ControlledTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(ControlledTank)) { UE_LOG(LogTemp, Error, TEXT("Not possessing tank!")); }
	if (!ensure(PlayerTank)) { UE_LOG(LogTemp, Error, TEXT("Can't find player tank!")); }

}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();

	if (CheckForReload()) { ControlledTank->FindComponentByClass<UTankAimingComponent>()->Reload(); }

}

bool ATankAIController::CheckForReload() const {

	return ControlledTank->FindComponentByClass<UTankAimingComponent>()->GetCurrentAmmoStock() == 0;

}
