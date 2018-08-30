// Copyright FairgroundPandaStudio

#include "TankTrack.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float SidewaysSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CorrectionAcceleration = -1 * SidewaysSpeed / DeltaTime * GetRightVector();
	UStaticMeshComponent* TankRoot = dynamic_cast<UStaticMeshComponent*>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Divide by 2 as 2 tracks
	//TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {

	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = dynamic_cast<UPrimitiveComponent*>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return;

}

