// Copyright FairgroundPandaStudio

#include "SpringWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetRelativeLocation(FVector(0.0f, 0.0f, -150.0f));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(FName("None"), 1000.0f, true);
	Wheel->SetCollisionProfileName(FName("PhysicsActor"));	

	ApplyDefaultSpringSettings();

}

void ASpringWheel::ApplyDefaultSpringSettings() {

	Spring->SetConstrainedComponents(Mass, NAME_None, Wheel, NAME_None);

	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);

	Spring->SetLinearPositionTarget(FVector(0.0f, 0.0f, 0.0f));
	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityTarget(FVector(0.0f, 0.0f, 0.0f));
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(500.0f, 100.0f, 0.0f);

}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();		
	
	SetupNewMass();
	
}

void ASpringWheel::SetupNewMass() {

	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = dynamic_cast<UPrimitiveComponent*>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	Mass = BodyRoot;
	Spring->SetConstrainedComponents(Mass, NAME_None, Wheel, NAME_None);

}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

