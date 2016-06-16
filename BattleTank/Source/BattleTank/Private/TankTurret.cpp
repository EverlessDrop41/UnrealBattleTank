// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankTurret.h"


void UTankTurret::Yaw(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
}

