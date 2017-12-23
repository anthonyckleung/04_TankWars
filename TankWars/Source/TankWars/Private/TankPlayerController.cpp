// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()) );
	}
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}






void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString() );
	//Get world location through crosshair by ray tracing
	//If it hits the landscape
		//Tell controlled tank to aim at this point
	if ( GetSightRayHitLocation(HitLocation) )
	{
		UE_LOG( LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString() );
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
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
		 GetLookVectorHitLocation(WorldDirection, OutHitLocation);
	}

	return true;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>( GetPawn() );
	
}
