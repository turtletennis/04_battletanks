// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {

	float ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto DeltaRotation = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + DeltaRotation;
	//UE_LOG(LogTemp, Warning, TEXT("New Rotation: %f"), RawNewRotation)
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}


