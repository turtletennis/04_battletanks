// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTankTrack;
/**
 * Responsible for moving a tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float Throw);
	//Initialises the component, setting the left and right tank tracks.
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankTrack *Left, UTankTrack *Right);
private:
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
	
};
