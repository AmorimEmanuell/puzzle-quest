// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = GetOwner();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!IsMoving)
	{
		return;
	}

	ElapsedRotateDuration += DeltaTime;
	float RotAlpha = FMath::Clamp(ElapsedRotateDuration / RotateDuration, 0, 1);
	FRotator SetpRotation = FMath::Lerp(CurrentRotation, TargetRotation, RotAlpha);
	MyOwner->SetActorRotation(SetpRotation);

	ElapsedMovementDuration += DeltaTime;
	float Alpha = FMath::Clamp(ElapsedMovementDuration / MovementDuration, 0, 1);
	FVector StepLocation = FMath::Lerp(CurrentLocation, TargetLocation, Alpha);
	MyOwner->SetActorLocation(StepLocation);

	if (Alpha == 1)
	{
		IsMoving = false;
	}
}

void UMover::AttemptMove(FVector MoveDirection)
{
	if (IsMoving)
	{
		return;
	}

	CurrentLocation = MyOwner->GetActorLocation();
	TargetLocation = CurrentLocation + MoveDirection * MoveDistance;

	CurrentRotation = MyOwner->GetActorRotation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);

	ElapsedMovementDuration = 0;
	ElapsedRotateDuration = 0;

	IsMoving = true;
}

bool UMover::CanMove()
{
	return !IsMoving;
}
