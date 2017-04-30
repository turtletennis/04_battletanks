// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankAimingComponent;
class UTankTurret;
class AProjectile;
class UTankTrack;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelReference);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretReference);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetLeftTrackReference(UTankTrack* TrackReference);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRightTrackReference(UTankTrack* TrackReference);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float FireSpeed = 5000;	//sensible starting value of 50m/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* AimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UTankBarrel *Barrel = nullptr;
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
};
