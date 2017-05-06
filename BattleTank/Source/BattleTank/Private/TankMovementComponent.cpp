// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	
}

void UTankMovementComponent::Initialise(UTankTrack *Left, UTankTrack *Right)
{
	LeftTrack = Left;
	RightTrack = Right;
	//TODO: prevent double speed due to using triggers and left stick
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super() as we're replacing the functionality
	auto VelocityString = MoveVelocity.ToString();
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Requesting move: %s"), *Name,*VelocityString);
}