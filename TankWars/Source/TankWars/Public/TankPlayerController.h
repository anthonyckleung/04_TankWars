// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKWARS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	ATank* GetControlledTank() const;
	
	
	

	void AimTowardsCrosshair(); //Moves tank barrel so that a shot would hit where the crosshair aims at.
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;  //Return an OUT parameter, true if hit landscape
	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000000; //10 km

	UPROPERTY( EditAnywhere )
	float CrossHairXLocation = 0.5f;

	UPROPERTY( EditAnywhere )
	float CrossHairYLocation = 0.3333f;
};
