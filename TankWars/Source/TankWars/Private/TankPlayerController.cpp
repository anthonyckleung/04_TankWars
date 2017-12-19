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
	UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString() );
	//Get world location through crosshair by ray tracing
	//If it hits the landscape
		//Tell controlled tank to aim at this point
	GetSightRayHitLocation(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString() );

	// "de-project" the screen position of the crosshair to a world direction
	// Linetrace through along that look direction and see what was hit (up to max range)
	return true;
}


ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>( GetPawn() );
	
}
