// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankTrack.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::Initialise(UTankBarrel* BarrelReference, UTankTurret* TurretReference, UTankTrack* LeftTrackReference, UTankTrack* RightTrackReference, UTankMovementComponent* MovementComponentToSet)
{
	AimingComponent->SetBarrelReference(BarrelReference);
	Barrel = BarrelReference;
	AimingComponent->SetTurretReference(TurretReference);
	LeftTrack = LeftTrackReference;
	RightTrack = RightTrackReference;
	MovementComponent = MovementComponentToSet;
	MovementComponent->Initialise(LeftTrack, RightTrack);
	TArray<UPrimitiveComponent*> MyComponents;
	MyComponents.Add(Barrel);
	MyComponents.Add(TurretReference);
	MyComponents.Add(LeftTrack);
	MyComponents.Add(RightTrack);
	//tank body \/
	MyComponents.Add(Cast<UPrimitiveComponent>(GetRootComponent()));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetOwner());

	for (int i = 0; i < MyComponents.Num(); i++)
	{
		MyComponents[i]->MoveIgnoreComponents = MyComponents;
		MyComponents[i]->MoveIgnoreActors = IgnoreActors;
	}
	for (int i = 0; i < MyComponents.Num(); i++)
	{
		MyComponents[i]->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		MyComponents[i]->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MyComponents[i]->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	}
	UE_LOG(LogTemp, Warning, TEXT("Tank Initialisation completed"))
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation,FireSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelReference)
{
	AimingComponent->SetBarrelReference(BarrelReference);
	Barrel = BarrelReference;
}

void ATank::SetLeftTrackReference(UTankTrack* TrackReference) 
{
	LeftTrack = TrackReference;
}

void ATank::SetRightTrackReference(UTankTrack* TrackReference)
{
	RightTrack = TrackReference;
}


void ATank::SetTurretReference(UTankTurret* TurretReference)
{
	AimingComponent->SetTurretReference(TurretReference);
}

void ATank::Fire()
{
	auto OurTankName = GetName();
	
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && IsReloaded) {
		// spawn a projectile at the socket location
		auto SocketTransform = Barrel->GetSocketTransform(FName("ProjectileOrigin"));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketTransform.GetLocation(), SocketTransform.GetRotation().Rotator(), SpawnParameters);
		NewProjectile->LaunchProjectile(FireSpeed);
		UE_LOG(LogTemp, Warning, TEXT("%s fired from %s"), *OurTankName, *NewProjectile->GetActorLocation().ToString());
		LastFireTime = FPlatformTime::Seconds();
	}
}