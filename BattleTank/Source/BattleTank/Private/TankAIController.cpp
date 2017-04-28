// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ErrorProbability = FMath::Clamp(ErrorProbability, 0.0f, 1.0f);
	APawn* pawn = GetPawn();
	ControlledTank = Cast<ATank>(pawn);

	auto playerController = GetWorld()->GetFirstPlayerController();
	PlayerTank = Cast<ATank>(Cast<ATankPlayerController>(playerController)->GetControlledTank());
	
}

void ATankAIController::AimAtPlayer() {
	auto aimLocation = PlayerTank->GetActorLocation();
	if (FMath::RandRange(0.0f, 1.0f) < ErrorProbability) {
		aimLocation += FMath::VRand()*ErrorBounds;
	}
	ControlledTank->AimAt(aimLocation);
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimAtPlayer();
	ControlledTank->Fire();
}