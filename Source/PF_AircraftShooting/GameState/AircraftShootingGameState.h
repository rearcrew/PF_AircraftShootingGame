// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AircraftShootingGameState.generated.h"

/**
 * 
 */
UCLASS()
class PF_AIRCRAFTSHOOTING_API AAircraftShootingGameState : public AGameState
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "ResultPage")
		void ShowResultPage(bool bWin);
};
