// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"




void ATankAIController::BeginPlay() {

	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playertank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledtank= GetPawn();

	if (!playertank && !controlledtank) { return; }
	

		MoveToActor(playertank, radius);

		auto aimingcomponent = controlledtank->FindComponentByClass<UTankAimingComponent>();

		aimingcomponent->AimAt(playertank->GetActorLocation());
		aimingcomponent->fire();
		

		
	
}





