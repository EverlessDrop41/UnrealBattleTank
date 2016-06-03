// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAIController.h"
#include "../TankPlayerController.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	ATankPlayerController* TPC = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	return TPC->GetControlledTank();
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* ThisTank = GetControlledTank();

	if (!ThisTank)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("[TAIC] AI Tank not found"));
	}

	ATank* PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("[TAIC] Player Tank %s found!"), *PlayerTank->GetName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("[TAIC] Player Tank not found"));
	}
}