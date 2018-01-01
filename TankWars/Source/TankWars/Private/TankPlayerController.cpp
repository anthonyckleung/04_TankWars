// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent =GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent) )
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController cannot find aiming component"));
	}
	//auto ControlledTank = GetControlledTank();
	/*if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()) );
	}*/
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}



void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank()) ) { return; }

	FVector HitLocation; //Out parameter
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString() );

	//Get world location through crosshair by ray tracing
	//If it hits the landscape
		//Tell controlled tank to aim at this point
	if ( GetSightRayHitLocation(HitLocation) )
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString() );
	
	
	FVector WorldDirection; //Unit vector in the direction we are looking.
	// "de-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, WorldDirection)) 
	{
		// Linetrace through along that look direction and see what was hit (up to max range)
		return GetLookVectorHitLocation(WorldDirection, HitLocation);
	}

	return false;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>( GetPawn() );
	
}
