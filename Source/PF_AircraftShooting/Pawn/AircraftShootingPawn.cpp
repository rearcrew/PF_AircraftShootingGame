// Fill out your copyright notice in the Description page of Project Settings.

#include "AircraftShootingPawn.h"
#include "PF_AircraftShooting.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/StaticMesh.h"
#include "Engine/CollisionProfile.h"

#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// My Header File
#include "Interface//PawnEventInterface.h"

#include "GameMode//AircraftShootingGameMode.h"
#include "Projectile//AircraftShootingProjectile.h"

const FName AAircraftShootingPawn::MoveForwardBinding("MoveForward");
const FName AAircraftShootingPawn::MoveRightBinding("MoveRight");

const FName AAircraftShootingPawn::StartFireBinding("StartFire");

// Sets default values
AAircraftShootingPawn::AAircraftShootingPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetupAttachment(RootComponent);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	
	UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
	if (CapsuleComponent != nullptr)
	{
		CapsuleComponent->InitCapsuleSize(50.0f, 50.0f);
	}

	// Movement
	MaxMoveSpeed = 1000.0f;
	//// Weapon
	FireOffset = FVector(90.f, 0.f, 0.f);
	FireInterval = 0.1f;
	bFireAction = false;
}

// Called when the game starts or when spawned
void AAircraftShootingPawn::BeginPlay()
{
	auto CharacterMovement = GetCharacterMovement();
	if (CharacterMovement != nullptr)
	{
		CharacterMovement->MaxWalkSpeed = MaxMoveSpeed;
	}

	SetHealth(MaxHealth);

	Super::BeginPlay();
}

float AAircraftShootingPawn::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DecreaseHealth(DamageAmount);

	if (IsDeadPawn())
	{
		AAircraftShootingGameMode* GameMode = GetWorld()->GetAuthGameMode<AAircraftShootingGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->CheckEndGame();
		}

		IPawnEventInterface* PawnEventInterface = Cast<IPawnEventInterface>(DamageCauser);
		if (PawnEventInterface != nullptr)
		{
			PawnEventInterface->AddScore(100);
		}
	}

	return ActualDamage;
}

void AAircraftShootingPawn::OnStartFire()
{
	if (bFireAction)
	{
		return;
	}
	bFireAction = true;

	if (GetWorldTimerManager().IsTimerActive(Handle_WeaponFiring))
	{
		return;
	}

	ProcessWeaponFiring();
}

void AAircraftShootingPawn::OnStopFire()
{
	bFireAction = false;
}

void AAircraftShootingPawn::ProcessWeaponFiring()
{
	GetWorldTimerManager().ClearTimer(Handle_WeaponFiring);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &AAircraftShootingPawn::DoWeaponFiring);
	GetWorldTimerManager().SetTimer(Handle_WeaponFiring, TimerDelegate, FireInterval, true, 0.f);
}

void AAircraftShootingPawn::DoWeaponFiring()
{
	if (!bFireAction)
	{
		GetWorldTimerManager().ClearTimer(Handle_WeaponFiring);
		return;
	}

	const FRotator FireRotation = GetActorRotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(FireOffset);
	
	// Spawn Projectile
	UWorld* const World = GetWorld();
	if (World != NULL && ProjectileClass != nullptr)
	{
		FActorSpawnParameters ActorSpawnparameters;
		ActorSpawnparameters.Owner = GetOwner();
		ActorSpawnparameters.Instigator = this;

		// spawn the projectile
		auto Projectile = World->SpawnActor<AAircraftShootingProjectile>(ProjectileClass, SpawnLocation, FireRotation, ActorSpawnparameters);
		if (Projectile!= nullptr && FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}

void AAircraftShootingPawn::SetHealth(float NewHealth)
{
	Health = NewHealth;
	OnUpdateHealthUI.Broadcast();
}

void AAircraftShootingPawn::DecreaseHealth(float DecreaseValue)
{
	int OldHealth = Health;

	Health = FMath::Max<int32>(0, Health - DecreaseValue);
	if (OldHealth == Health)
	{
		return;
	}

	OnUpdateHealthUI.Broadcast();
	if (Health == 0)
	{
		Destroy();
	}
}