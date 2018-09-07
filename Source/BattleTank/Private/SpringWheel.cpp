// Copyright FairgroundPandaStudio

#include "SpringWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);
	Axle->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
	Axle->SetSimulatePhysics(true);
	Axle->SetMassOverrideInKg(FName("None"), 1000.0f, true);
	Axle->SetCollisionProfileName(FName("OverlapAll"));
	Axle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(FName("None"), 1000.0f, true);
	Wheel->SetCollisionProfileName(FName("PhysicsActor"));
	Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);

	ApplyDefaultSpringSettings();
	ApplyDefaultAxleSettings();	

}

void ASpringWheel::ApplyDefaultSpringSettings() {

	Spring->SetConstrainedComponents(Mass, NAME_None, Axle, NAME_None);

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

void ASpringWheel::ApplyDefaultAxleSettings() {

	AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);

	AxleConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();		
	
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASpringWheel::OnComponentHit);

	SetupNewMass();
	
}

void ASpringWheel::SetupNewMass() {

	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = dynamic_cast<UPrimitiveComponent*>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	Mass = BodyRoot;
	Spring->SetConstrainedComponents(Mass, NAME_None, Axle, NAME_None);
	AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);

}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TotalForceMagnitudeThisFrame = 0.0f;

}

void ASpringWheel::AddDrivingForce(float ForceMagnitude){

	TotalForceMagnitudeThisFrame += ForceMagnitude;

}

void ASpringWheel::ApplyForce() {

	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);

}

void ASpringWheel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	ApplyForce();

}
