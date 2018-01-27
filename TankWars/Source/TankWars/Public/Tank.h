// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraShake.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKWARS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

	//Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	//Return current health as a % of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShake> CameraShake;

	FTankDelegate OnDeath;

private:	
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int StartingHealth = 100.f;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int CurrentHealth ; // Initialized in BeginPlay

	
	
};
