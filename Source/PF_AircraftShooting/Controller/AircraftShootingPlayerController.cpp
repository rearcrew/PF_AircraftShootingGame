// Fill out your copyright notice in the Description page of Project Settings.

#include "AircraftShootingPlayerController.h"

#include "PF_AircraftShooting.h"

void AAircraftShootingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		InputComponent->BindAxisKey(EKeys::MouseY, this, &AAircraftShootingPlayerController::EventAxisMouseY);
	}
}

void AAircraftShootingPlayerController::EventAxisMouseY(float AxisValue)
{
	if (GetPawn() == nullptr)
	{
		return;
	}

	FRotator MouseRotation = GetMouseRotation();
	SetPawnRotationInput(MouseRotation);
}

FRotator AAircraftShootingPlayerController::GetMouseRotation()
{
	FVector2D MousePostion;
	GetMousePosition(MousePostion.X, MousePostion.Y);

	FVector2D PawnPosition;
	ProjectWorldLocationToScreen(GetPawn()->GetActorLocation(), PawnPosition);

	FVector2D CalcVector = MousePostion - PawnPosition;

	CalcVector.Y *= -1.f;

	return FRotator(0.f, (180.f) / PI * FMath::Atan2(CalcVector.X, CalcVector.Y), 0.f);
}

void AAircraftShootingPlayerController::SetPawnRotationInput(FRotator MouseRotation)
{
	FRotator ActorRotation = GetPawn()->GetActorRotation();

	FRotator CalcRotator = MouseRotation - ActorRotation;
	CalcRotator.Normalize();

	float CalcYaw = CalcRotator.Yaw / InputYawScale;

	if (CalcYaw <= 0.f)
	{
		if (CalcYaw < -1.f)
		{
			AddYawInput(-1.f);
			return;
		}
		AddYawInput(CalcYaw);
		return;
	}

	if (CalcYaw > 1.f)
	{
		AddYawInput(1.f);
		return;
	}
	AddYawInput(CalcYaw);
	return;
}