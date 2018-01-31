// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"


UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay() {

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	//UE_LOG(LogTemp, Warning, TEXT("Im Hit"))
		ApplySideForce();
		DriveTrack();
		currentthrottle = 0;
}



void UTankTrack::ApplySideForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto tankroot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (tankroot->GetMass() * CorrectionAcceleration) / 2;

	tankroot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float throttle) {

	currentthrottle = FMath::Clamp<float>(currentthrottle + throttle, -1, 1);
	
}


void UTankTrack::DriveTrack() {

	auto ForceApplied = GetForwardVector()* currentthrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);



}