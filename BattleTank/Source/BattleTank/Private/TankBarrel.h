// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//Static mesh component for a tank barrel
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Elevate the barrel at a speed relative to the maximum rotation speed. Clamps from -1 to 1.
	void Elevate(float RelativeSpeed);

private:
	// Maximum angular velocity of the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5; 
	// Minimum elevation angle of the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinimumElevationDegrees = 0; 
	// Maximum elevation angle of the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaximumElevationDegrees = 30; // sensible starting value
	
};
