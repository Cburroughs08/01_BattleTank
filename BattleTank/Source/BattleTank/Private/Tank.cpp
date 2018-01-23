// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAiming = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATank::AimAt(FVector HitLocation) {
	TankAiming->AimAt(HitLocation, launchspeed);
	
}

void ATank::SetBarrelRef(UTankBarrel* BarrelSet) {

	TankAiming->SetBarrelRef(BarrelSet);
}

void ATank::SetTurretRef(UTankTurret* TurretSet) {

	TankAiming->SetTurretRef(TurretSet);

}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::fire() {


}