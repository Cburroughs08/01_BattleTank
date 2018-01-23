// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::TurnTurret(float target) {

	auto relativespeed = FMath::Clamp<float>(target, -1, 1);
	auto ElevationChange = relativespeed * Speed*GetWorld()->DeltaTimeSeconds;
	auto RawElevationChange = RelativeRotation.Yaw + ElevationChange;

	
	
	SetRelativeRotation(FRotator(0, RawElevationChange, 0));
}

