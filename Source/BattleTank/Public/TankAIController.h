// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Controller for AI Tanks
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

private:

	APawn* ControlledTank;
	APawn* PlayerTank;

	// How close enemy tank will get to player tank (in cms)
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius = 7000;

	bool CheckForReload() const;

	UFUNCTION()
	void OnPossessedTankDeath();

};
