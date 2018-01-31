// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {

	Reloading,
	Aiming,
	locked,
	OutofAmmo

};


class UTankBarrel;
class UTankTurret;
class AProjectile;

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

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState;


public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Fire")
		void fire();


	UTankBarrel * Barrel = nullptr;
	// UTankTurret
	UTankTurret* Turret = nullptr;

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	int GetRoundsLeft() const;

private:

	//UStaticMeshComponent * Barrel = nullptr;

	void MoveBarrel(FVector AimDirection);
	
	void MoveTurret(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = Firing)
		float launchspeed = 20000.f;


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	bool IsBarrelMoving();

	double LastFireTime;
	float ReloadTime = 3.f;

	FVector aimdirection;

	int RoundsLeft = 3;
};
