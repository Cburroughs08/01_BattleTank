// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (getPlayertank()) {

		getControlledTank()->AimAt(getPlayertank()->GetActorLocation());
	}
}


ATank * ATankAIController::getControlledTank()	const {

	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::getPlayertank() const{

	auto playerpawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerpawn) { return nullptr; }
	return Cast<ATank>(playerpawn);
	
}
