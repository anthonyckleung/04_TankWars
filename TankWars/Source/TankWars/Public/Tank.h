// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations

UCLASS()
class TANKWARS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	

	
	virtual void BeginPlay();

	
	


private:	
	// Sets default values for this pawn's properties
	ATank();
	

	// Local barrel pointer reference
	
	//UTankTurret* Turret = nullptr;

	
	
};
