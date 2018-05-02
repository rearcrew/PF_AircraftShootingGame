// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AircraftShootingGameMode.generated.h"

UCLASS(MinimalAPI)
class AAircraftShootingGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAircraftShootingGameMode();

	virtual void HandleMatchHasEnded() override;

	void CheckEndGame();

private:
	bool bWinGame;
};