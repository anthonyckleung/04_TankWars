// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class TANKWARS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	

	
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	


private:	
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	// Local barrel pointer reference
	UTankBarrel* Barrel = nullptr; //TODO remove
	//UTankTurret* Turret = nullptr;

	double LastFireTime = 0;
	
};
