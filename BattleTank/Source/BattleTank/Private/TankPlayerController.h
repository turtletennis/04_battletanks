// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//must be the last include
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		ATank* GetControlledTank() const;

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation=0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation=0.25;
	UPROPERTY(EditAnywhere)
	float RayCastDistance=500000;

	void GetCrosshairScreenLocation(FVector2D& ScreenLocation) const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	bool LineTrace(FVector Start, FVector Direction, TArray<FHitResult> &HitResults) const;
};
