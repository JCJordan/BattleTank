// Copyright FairgroundPandaStudio

#include "SpringWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);
	Mass->SetSimulatePhysics(true);
	Mass->SetMassOverrideInKg(FName("None"), 10000.0f, true);
	Mass->SetCollisionProfileName(FName("PhysicsActor"));

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Mass, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetRelativeLocation(FVector(0.0f, 0.0f, -400.0f));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(FName("None"), 100.0f, true);
	Wheel->SetCollisionProfileName(FName("PhysicsActor"));

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	Spring->AttachToComponent(Mass, FAttachmentTransformRules::KeepRelativeTransform);
	Spring->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
	ApplyDefaultSpringSettings();

}

void ASpringWheel::ApplyDefaultSpringSettings() {

	Spring->SetConstrainedComponents(Mass, FName("None"), Wheel, FName("None"));

	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);

	Spring->SetLinearPositionTarget(FVector(0.0f, 0.0f, 0.0f));
	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityTarget(FVector(0.0f, 0.0f, 0.0f));
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(5000.0f, 1000.0f, 0.0f);

}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

