// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



protected:


	

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);



private:


	void AimTowardCrosshairs();

	bool GetRayHitLocation(FVector& HitLocation) const;

	bool GetLookHitLocation(FVector LookDirection, FVector& HitLocation) const;

	bool GetLookDirection(FVector2D,FVector&) const;

	UPROPERTY(EditAnywhere)
		float CrosshairX = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.3333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;


};
