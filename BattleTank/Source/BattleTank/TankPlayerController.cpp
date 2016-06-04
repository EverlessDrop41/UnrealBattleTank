// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* tank = GetControlledTank();

	if (tank) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("[TPC] Tank %s found!"), *tank->GetName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("[TPC] Tank not found"));
	}

}

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//DoStuff
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//Get the direction to look in
	FVector LookDirection;

	if (GetLookDirection(LookDirection)) {
		
		if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
			//GetControlledTank()->AimAt(HitLocation);
		}
	}

	//Line trace along that look direction, and see what we hit
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FVector StartPos = PlayerCameraManager->GetCameraLocation();
	FVector EndPos = StartPos + (LookDirection * LineTraceRange);
	FHitResult HitResult;

	bool didHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartPos,
		EndPos,
		ECC_Visibility
	);

	if (didHit) {
		HitLocation = HitResult.Location;
	} else {
		HitLocation = FVector(0);
	}

	return didHit;
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());			
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const {
	//Get the crosshair screen position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	FVector WorldLocation;
	//Turn that screen position into a look direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection
	);
}