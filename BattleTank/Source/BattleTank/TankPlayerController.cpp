// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn NOT found"));
	}
	
	return	Cast<ATank>(pawn);

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//raycast to world
	//if it hits the landscape, aim at the point of intersection

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController AimTowardsCrosshair()"));
}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay()"));
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}


