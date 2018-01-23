// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelRef(UTankBarrel* BarrelSet);
	// Set Turret Ref
	void SetTurretRef(UTankTurret* TurretSet);

	UTankBarrel * Barrel = nullptr;
	// UTankTurret
	UTankTurret* Turret = nullptr;

private:

	//UStaticMeshComponent * Barrel = nullptr;

	void MoveBarrel(FVector AimDirection);
	
	void MoveTurret(FVector AimDirection);
};