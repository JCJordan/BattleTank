// Copyright FairgroundPandaStudio

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* AInstigator, AActor* DamageCauser) {

	int32 DamageToApply = FMath::Clamp(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) { OnDeath.Broadcast(); }

	return DamageToApply;

}

float ATank::GetHealthPercent() const {
	
	return static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);

}
