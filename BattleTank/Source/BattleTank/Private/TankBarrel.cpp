// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	
	float ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto DeltaElevation = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + DeltaElevation;
	auto ClampedNewElevation = FMath::Clamp(RawNewElevation, MinimumElevationDegrees, MaximumElevationDegrees);
	SetRelativeRotation(FRotator(ClampedNewElevation, 0, 0));
}


