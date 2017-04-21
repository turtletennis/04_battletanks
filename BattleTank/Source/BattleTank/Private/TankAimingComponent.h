// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"


class UTankBarrel;
//Responsible for aiming a tank's weapon
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelReference);
	void SetTurretReference(UStaticMeshComponent* TurretReference);

protected:


private:
	UTankBarrel* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;
	void MoveBarrelTowards(FVector Angle);
};
