// Fill out your copyright notice in the Description page of Project Settings.

#include "AircraftShootingPlayerPawn.h"

#include "Components/InputComponent.h"

void AAircraftShootingPlayerPawn::AddScore(int32 AddScoreValue)
{
	Score += AddScoreValue;
	OnUpdateScoreUI.Broadcast();
}

void AAircraftShootingPlayerPawn::OnMoveForward(float AxisValue)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f), AxisValue, true);
}

void AAircraftShootingPlayerPawn::OnMoveRight(float AxisValue)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f), AxisValue, true);
}

// Called to bind functionality to input
void AAircraftShootingPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding, this, &AAircraftShootingPlayerPawn::OnMoveForward);
	PlayerInputComponent->BindAxis(MoveRightBinding, this, &AAircraftShootingPlayerPawn::OnMoveRight);

	PlayerInputComponent->BindAction(StartFireBinding, IE_Pressed, this, &AAircraftShootingPlayerPawn::OnStartFire);
	PlayerInputComponent->BindAction(StartFireBinding, IE_Released, this, &AAircraftShootingPlayerPawn::OnStopFire);
}

