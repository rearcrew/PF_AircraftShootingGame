// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AircraftShootingPawn.generated.h"

UCLASS()
class PF_AIRCRAFTSHOOTING_API AAircraftShootingPawn : public ACharacter
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateUIDelegate);

public:
	AAircraftShootingPawn(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void OnStartFire();
	void OnStopFire();

	void ProcessWeaponFiring();
	void DoWeaponFiring();

	void SetHealth(float NewHealth);
	void DecreaseHealth(float DecreaseValue);

	bool IsDeadPawn() { return Health <= 0; };

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName StartFireBinding;
	
public:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MaxMoveSpeed;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		FVector FireOffset;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float FireInterval;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadOnly)
		class USoundBase* FireSound;

	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AAircraftShootingProjectile> ProjectileClass;

	UPROPERTY(Category = Gameplay, BlueprintReadOnly)
		int32 Health;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		int32 MaxHealth;

	UPROPERTY(BlueprintAssignable)
		FUpdateUIDelegate OnUpdateHealthUI;

	bool bFireAction;
	FTimerHandle Handle_WeaponFiring;
};
