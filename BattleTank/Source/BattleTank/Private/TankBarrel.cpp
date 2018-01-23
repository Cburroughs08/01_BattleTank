// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float degrees) {
	
	UE_LOG(LogTemp, Warning, TEXT("Elevate at %f"), degrees)

	auto relativespeed = FMath::Clamp<float>(degrees, -1, 1);
	auto ElevationChange = relativespeed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawElevationChange = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawElevationChange, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
