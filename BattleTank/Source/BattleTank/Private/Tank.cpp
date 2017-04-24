// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
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


void ATank::SetTurretReference(UTankTurret* TurretReference)
{
	AimingComponent->SetTurretReference(TurretReference);
}

void ATank::Fire()
{
	auto OurTankName = GetName();
	

	if (!Barrel) { 
		UE_LOG(LogTemp, Warning, TEXT("Barrel not set"));
		return; 
	}

	// spawn a projectile at the socket location
	auto SocketTransform = Barrel->GetSocketTransform(FName("ProjectileOrigin"));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketTransform.GetLocation(), SocketTransform.GetRotation().Rotator(),SpawnParameters);
	NewProjectile->LaunchProjectile(FireSpeed);
	UE_LOG(LogTemp, Warning, TEXT("%s fired from %s"), *OurTankName,*NewProjectile->GetActorLocation().ToString());
	//NewProjectile->
}