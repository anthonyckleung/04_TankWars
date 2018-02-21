// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"



// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankAimingComponent->Initialize(Barrel, Turret);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) //When dead
	{
		OnDeath.Broadcast();
	}

	if (PC != nullptr && CameraShake != nullptr)
	{
		PC->ClientPlayCameraShake(CameraShake, 1); //Play camera shake
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float) CurrentHealth / (float) StartingHealth;
}


void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay to Run

	CurrentHealth = StartingHealth;
}







