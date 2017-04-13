// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn found: %s"), *pawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn NOT found"));
	}

	return	Cast<ATank>(pawn);

}


ATank* ATankAIController::GetPlayerControlledTank() const
{
	auto playerController = GetWorld()->GetFirstPlayerController();
	if (playerController) {

		APawn* tank = Cast<ATankPlayerController>(playerController)->GetControlledTank();
		if (tank != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Pawn found by AI: %s"), *tank->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Pawn NOT found by AI"));
		}

		return	Cast<ATank>(tank);
	}

	return nullptr;

}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay()"));
	GetControlledTank();
	GetPlayerControlledTank();
}