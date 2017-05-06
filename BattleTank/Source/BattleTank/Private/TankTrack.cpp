// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto AlterAngle = FRotator(TrackForcePitch, 0, 0);
	if (Throttle < 0) {
		AlterAngle.Pitch = -TrackForcePitch;
	}
	ForceApplied = AlterAngle.RotateVector(ForceApplied);
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Force applied: %s"), *ForceApplied.ToString());
}