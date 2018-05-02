// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/AircraftShootingPawn.h"
#include "AircraftShootingAIPawn.generated.h"

/**
 * 
 */
UCLASS()
class PF_AIRCRAFTSHOOTING_API AAircraftShootingAIPawn : public AAircraftShootingPawn
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable)
		void StartFire();
	UFUNCTION(BlueprintCallable)
		void StopFire();
};
