// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;

}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
//void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

void UTankAimingComponent::AimAt(FVector HitLocation) {

	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		launchspeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)

		)
	{
	    aimdirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimdirection);
		MoveTurret(aimdirection);

		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *aimdirection.ToString())
	}

		
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	if (!Barrel) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection) {

	if (!Turret) { return; }
	auto BarrelRotator = Turret->GetForwardVector().Rotation();
	
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator =  AimAsRotator - BarrelRotator ;
	

	Turret->TurnTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::fire() {

	

	if (FiringState != EFiringState::Reloading) {

		if (!Barrel ) { return; }
		if (!ProjectileBlueprint) { return; }
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->LaunchProjectile(launchspeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	//UE_LOG(LogTemp, Warning, TEXT("Ticking"))
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime) {

		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {

		FiringState = EFiringState::Aiming;
	}
	else {

		FiringState = EFiringState::locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {

	if (!Barrel) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(aimdirection, 0.01);

}