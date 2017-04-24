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
void ATankPlayerController::GetCrosshairScreenLocation(FVector2D& ScreenLocation) const
{
	int32 ViewportSizeX, ViewportSizeY, ScreenX, ScreenY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	ScreenX = ViewportSizeX * CrosshairXLocation;
	ScreenY = ViewportSizeY * CrosshairYLocation;
	ScreenLocation.X = ViewportSizeX * CrosshairXLocation;
	ScreenLocation.Y = ViewportSizeY * CrosshairYLocation;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector2D CrosshairLocation;
	GetCrosshairScreenLocation(CrosshairLocation);
	
	FVector WorldLocation;
	FVector WorldDirection;

	if (DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, WorldLocation, WorldDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("World location: %s World direction: %s"), *WorldLocation.ToString(), *WorldDirection.ToString());
	}
	
	TArray<FHitResult> HitResults = TArray<FHitResult>();
	
	if (LineTrace(WorldLocation, WorldDirection, HitResults)) {
		bool aimingThroughPlayer = false;
		for (int i = 0; i < HitResults.Num(); i++) {
			FHitResult HitResult = HitResults[i];
			if (HitResult.IsValidBlockingHit()) {
				if (HitResult.GetActor() != GetControlledTank()) {
					if (aimingThroughPlayer)
					{
						UE_LOG(LogTemp, Warning, TEXT("Aiming through player tank actor, next hit is: %s"), *HitResult.ImpactPoint.ToString());
					}

					HitLocation = HitResult.ImpactPoint;
					return true;
				}else
				{
					aimingThroughPlayer = true;
					UE_LOG(LogTemp, Warning, TEXT("%i hits, aiming through player tank actor: %s"),HitResults.Num(), *HitResult.ImpactPoint.ToString());
				}
			}
			else
			{
				HitLocation = FVector(0);
				return false;
			}
		}
		
	}

	return false;
}

bool ATankPlayerController::LineTrace(FVector Start, FVector Direction, TArray<FHitResult> &HitResults) const
{
	FVector End = Start + Direction * RayCastDistance;
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = true;
	RV_TraceParams.AddIgnoredActor(GetControlledTank());
	
	//do the line trace
	return GetWorld()->LineTraceMultiByChannel(
		HitResults,        //result
		Start,        //start
		End,        //end
		ECC_Visibility,    //collision channel
		RV_TraceParams
	);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	else 
	{
		//UE_LOG(LogTemp, Warning, TEXT("No hit found"));
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


