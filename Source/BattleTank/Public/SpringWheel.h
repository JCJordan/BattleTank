// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

class UStaticMeshComponent;
class UPrimitiveComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void SetupNewMass();
	void ApplyDefaultSpringSettings();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPrimitiveComponent* Mass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* Spring = nullptr;
	
};
