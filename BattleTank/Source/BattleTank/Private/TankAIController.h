// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"

#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//Used when calculating random error in AI aiming.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ErrorBounds = 8000.0f;

	//Probability of random aiming error
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ErrorProbability = 1.5;

private:
	
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;
	void BeginPlay() override;
	void AimAtPlayer();
	virtual void Tick(float DeltaSeconds) override;

	
};
