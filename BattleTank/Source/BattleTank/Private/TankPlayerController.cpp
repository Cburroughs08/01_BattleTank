// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"




void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	auto Aimingcomponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (Aimingcomponent) {

		FoundAimingComponent(Aimingcomponent);

	}
	else {


	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardCrosshairs();
}





void ATankPlayerController::AimTowardCrosshairs(){

	if (!GetPawn()) { return; }
	auto Aimingcomponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!Aimingcomponent) { return; }

	FVector HitLocation;

	if (GetRayHitLocation(HitLocation)) {

		Aimingcomponent->AimAt(HitLocation);
	}
	

	
}


bool ATankPlayerController::GetRayHitLocation(FVector& HitLocation) const {

	int32 ViewPortSizeX, ViewportSizeY;
	GetViewportSize(ViewPortSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrosshairX, ViewportSizeY*CrosshairY);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLoc %s"), *ScreenLocation.ToString())

	FVector LookDirection;

	if (GetLookDirection(ScreenLocation,LookDirection)) {
	
		GetLookHitLocation(LookDirection, HitLocation);
	
	}
		return true;
}


bool ATankPlayerController::GetLookHitLocation(FVector LookDirection, FVector& HitLocation) const {

	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {

		HitLocation=HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}



bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {


	FVector CamerWorldLocation;

	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamerWorldLocation, LookDirection));

}