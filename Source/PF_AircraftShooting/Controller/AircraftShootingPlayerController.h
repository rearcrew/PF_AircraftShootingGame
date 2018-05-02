// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AircraftShootingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PF_AIRCRAFTSHOOTING_API AAircraftShootingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;	
	
	void EventAxisMouseY(float AxisValue);

	FRotator GetMouseRotation();
	void SetPawnRotationInput(FRotator MouseRotation);
};
