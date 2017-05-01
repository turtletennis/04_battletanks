// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	//Set track throttle, for movement force
	UFUNCTION(BlueprintCallable, Category = Movement)
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 400000;	// in Newtons, assume 40 tonne tank, 10m/s/s acceleration
	//Alters the pitch that force is applied at (to prevent tank trying to drive into the ground)
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackForcePitch = 0.01;	// in Degrees
};
