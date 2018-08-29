// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

// Controller for AI Tanks
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	ATank* ControlledTank;
	ATank* PlayerTank;

	// How close enemy tank will get to player tank (in cms)
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius = 3000;



};
