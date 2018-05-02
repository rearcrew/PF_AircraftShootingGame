// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AircraftShootingGameMode.h"

#include "EngineUtils.h"

#include "Pawn//AircraftShootingAIPawn.h"
#include "Pawn//AircraftShootingPlayerPawn.h"

#include "GameState//AircraftShootingGameState.h"

AAircraftShootingGameMode::AAircraftShootingGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAircraftShootingPlayerPawn::StaticClass();

	bWinGame = false;
}

void AAircraftShootingGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	AAircraftShootingGameState* MyGameState = Cast<AAircraftShootingGameState>(GameState);
	if (MyGameState != nullptr)
	{
		MyGameState->ShowResultPage(bWinGame);
	}
}

void AAircraftShootingGameMode::CheckEndGame()
{
	APlayerController* MyPC = GetWorld()->GetFirstPlayerController();
	AAircraftShootingPawn* PlayerPawn = MyPC != nullptr ? Cast<AAircraftShootingPawn>(MyPC->GetPawn()) : nullptr;
	if (PlayerPawn == nullptr || PlayerPawn->IsPendingKillPending() || PlayerPawn->IsDeadPawn())
	{
		bWinGame = false;
		EndMatch();
		return;
	}

	bool bLiveEnemy = false;
	for (TActorIterator<AAircraftShootingAIPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AAircraftShootingAIPawn* AIPawn = *ActorItr;
		if (AIPawn != nullptr && !AIPawn->IsPendingKillPending() && !AIPawn->IsDeadPawn())
		{
			bLiveEnemy = true;
			break;
		}
	}

	if (bLiveEnemy)
	{
		return;
	}
	bWinGame = true;
	EndMatch();
}