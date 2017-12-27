// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame


	//Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationCharge = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationCharge;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, minElevation, maxElevation);
	SetRelativeRotation( FRotator(Elevation, 0, 0) );
}


