// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories= ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max down
	//+1 is max up movement
	//Move the Barrel Up/Down
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category= Elevation)
	float MaxDegreesPerSecond = 20;
	
	UPROPERTY(EditAnywhere, Category = Elevation)
	float MaxElevationDegrees = 25;

	UPROPERTY(EditAnywhere, Category = Elevation)
	float MinElevationDegrees = 0;
};
