// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelRef(UTankBarrel* BarrelSet) {

	Barrel = BarrelSet;

}


void UTankAimingComponent::SetTurretRef(UTankTurret* TurretSet) {

	Turret = TurretSet;

}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)

		)
	{
		auto aimdirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimdirection);
		MoveTurret(aimdirection);

		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *aimdirection.ToString())
	}

		
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection) {

	auto BarrelRotator = Turret->GetForwardVector().Rotation();
	
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator =  AimAsRotator - BarrelRotator ;
	

	Turret->TurnTurret(DeltaRotator.Yaw);
}