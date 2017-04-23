// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
 //Static mesh component for a tank turret
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//Rotate the barrel at a speed relative to the maximum rotation speed. Clamps from -1 to 1.
	void Rotate(float RelativeSpeed);

private:
	// Maximum angular velocity of the turret
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5;

};
