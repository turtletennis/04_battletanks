// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pawn found"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pawn NOT found"));
	}
	
	return	Cast<ATank>(pawn);

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector CameraLoc;
	FRotator CameraRot;
	GetActorEyesViewPoint(CameraLoc, CameraRot);

	FVector Start = CameraLoc;
	FVector End = Start + CameraRot.Vector() * RayCastDistance;

	FHitResult RV_Hit(ForceInit);
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = true;

	//  do the line trace
	bool DidTrace = GetWorld()->LineTraceSingleByChannel(
		RV_Hit,        //result
		Start,        //start
		End,        //end
		ECC_Pawn,    //collision channel
		RV_TraceParams
	);
	HitLocation = RV_Hit.ImpactPoint;
	return RV_Hit.IsValidBlockingHit();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector hitLocation;
	
	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Aim location: %s"), *hitLocation.ToString());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit found"));
	}
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


