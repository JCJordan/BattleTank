// Copyright FairgroundPandaStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

class USphereComponent;
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

	void AddDrivingForce(float ForceMagnitude);

private:

	void SetupNewMass();
	void ApplyDefaultSpringSettings();
	void ApplyDefaultAxleSettings();
	void ApplyForce();

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPrimitiveComponent* Mass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* Spring = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleConstraint = nullptr;
	
	float TotalForceMagnitudeThisFrame = 0.0f;

};
