// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	

	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	//Start the tank barrel moving towards the crosshair pointing location
	void AimTowardsCrosshair();
};
