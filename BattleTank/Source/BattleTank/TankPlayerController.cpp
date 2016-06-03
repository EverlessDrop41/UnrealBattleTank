// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

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
	//Get the world location thorugh crosshair linecast
	//If it hits a thing that can be hit
		//Tell the controlled tank to aim at it
}
