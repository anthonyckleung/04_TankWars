// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

//void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	if (!BarrelToSet) { return;  }
//	Barrel = BarrelToSet;
//
//}
//
//void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
//{
//	if (!TurretToSet) { return; }
//	Turret = TurretToSet;
//
//}




void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel) ) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel -> GetSocketLocation( FName("Projectile") );

	bool b_HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	// Calculate the OutLaunchVelocity

	if( b_HaveAimSolution )
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("Firing at: %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%f: Soln found!"), Time);
	}
	else
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No solns found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret) ) { return; }

	//Work out difference between current barrel aim direction, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG( LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString() );

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}

