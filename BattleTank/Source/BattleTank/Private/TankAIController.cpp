// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playertank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledtank= Cast<ATank>(GetPawn());

	if (playertank) {

		MoveToActor(playertank, radius);
		controlledtank->AimAt(playertank->GetActorLocation());
		//controlledtank->fire();
		

		
	}
}





