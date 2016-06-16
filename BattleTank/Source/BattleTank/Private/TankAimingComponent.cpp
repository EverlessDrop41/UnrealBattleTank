// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector Position, float LaunchSpeed) {
	if (!Barrel || !Turret) {
		UE_LOG(LogTemp, Error, TEXT("[TAC] Cannot Find Barrel And/Or Turret"));
		return; 
	}

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bCanAim = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		Position,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bCanAim) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: [TAC] Can Aim"), GetWorld()->GetTimeSeconds());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%f: [TAC] Cannot Aim"), GetWorld()->GetTimeSeconds());
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	//Move the barrel to match the aim directon
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;

	//Move the barrel given the max elevation speed
	Barrel->Elevate(DeltaRotator.Pitch); //TODO: Remove Magic Number
	Turret->Yaw(DeltaRotator.Yaw);

}