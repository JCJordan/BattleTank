// Copyright FairgroundPandaStudio

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/NavMovementComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	ControlledTank = dynamic_cast<ATank*>(GetPawn());
	PlayerTank = dynamic_cast<ATank*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(ControlledTank)) { UE_LOG(LogTemp, Error, TEXT("Not possessing tank!")); }
	if (!ensure(PlayerTank)) { UE_LOG(LogTemp, Error, TEXT("Can't find player tank!")); }

}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	if (ensure(PlayerTank)) {

		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}

}
