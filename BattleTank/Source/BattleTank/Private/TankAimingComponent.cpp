// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	auto BarrelPosition = Barrel->GetSocketLocation(FName("ProjectileOrigin"));
	FVector TossVelocity;
	auto OurTankName = GetOwner()->GetName();
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		BarrelPosition,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0
		,
		ESuggestProjVelocityTraceOption::DoNotTrace	//do not remove, required to avoid Engine bug
		))
	{
		FVector AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//get current barrel pitch and turret yaw

		//smoothly pitch the barrel and rotate the turret towards the aim direction
		
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming in direction: %s"), *OurTankName, *AimDirection.ToString());
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("%s could not hit location: %s"), *OurTankName, *HitLocation.ToString());
	}




	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelReference)
{
	Barrel = BarrelReference;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretReference)
{
	Turret = TurretReference;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("Aim direction as rotator: %s"), *AimDirectionAsRotator.ToString())
		auto DeltaRotator = AimDirectionAsRotator - BarrelRotator;
		Barrel->Elevate(DeltaRotator.Pitch);
		if (Turret) {
			Turret->Rotate(DeltaRotator.Yaw);
		}
}