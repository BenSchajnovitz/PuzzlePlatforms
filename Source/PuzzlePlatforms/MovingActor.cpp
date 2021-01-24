// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	}

	
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();
		FVector DirectionVector;

		if (JourneyTravelled >= JourneyLength)
		{
			FVector Swap = GlobalTargetLocation;
			GlobalTargetLocation = GlobalStartLocation;
			GlobalStartLocation = Swap;
		}

		DirectionVector = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

		Location += (DirectionVector * Speed * DeltaTime);
		SetActorLocation(Location);
	}

}
