// Copyright FairgroundPandaStudio

#include "TankTrack.h"
#include "Engine/World.h"
#include "SpawnPoint.h"
#include "SpringWheel.h"
#include "Components/PrimitiveComponent.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle) {

	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * MaxDrivingForce;

	TArray<ASpringWheel*> Wheels = GetWheels();

	float ForceAppliedPerWheel = ForceApplied / Wheels.Num();

	for (ASpringWheel* Wheel : Wheels) {

		Wheel->AddDrivingForce(ForceAppliedPerWheel);

	}

	return;
}

TArray<ASpringWheel*> UTankTrack::GetWheels() const {

	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);
	TArray<ASpringWheel*> Wheels;

	for (USceneComponent* Child : Children) {
		USpawnPoint* SpawnPoint = dynamic_cast<USpawnPoint*>(Child);
		if (SpawnPoint) {
			ASpringWheel* SpringWheel = dynamic_cast<ASpringWheel*>(SpawnPoint->GetSpawnedActor());
			if (SpringWheel) {
				Wheels.Add(SpringWheel);
			}
		}
	}

	return Wheels;

}

