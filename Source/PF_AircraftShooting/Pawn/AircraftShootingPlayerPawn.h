// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interface//PawnEventInterface.h"

#include "CoreMinimal.h"
#include "Pawn/AircraftShootingPawn.h"
#include "AircraftShootingPlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class PF_AIRCRAFTSHOOTING_API AAircraftShootingPlayerPawn : public AAircraftShootingPawn, public IPawnEventInterface
{
	GENERATED_BODY()

public:
	virtual void AddScore(int32 AddScoreValue) override;

	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);

	UPROPERTY(BlueprintAssignable)
		FUpdateUIDelegate OnUpdateScoreUI;

	UPROPERTY(Category = Gameplay, BlueprintReadOnly)
		int32 Score = 0;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
