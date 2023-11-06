// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnMoverComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "MapDefaultsSubSystem.h"

// Sets default values for this component's properties
UPawnMoverComponent::UPawnMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPawnMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = GetOwner();
	MapDefaultsSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMapDefaultsSubSystem>();
}

// Called every frame
void UPawnMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving)
	{
		return;
	}

	ElapsedDuration += DeltaTime;
	float Alpha = FMath::Clamp(ElapsedDuration / MovementDuration, 0, 1);
	FVector StepLocation = FMath::Lerp(CurrentLocation, TargetLocation, Alpha);
	MyOwner->SetActorLocation(StepLocation);

	if (Alpha == 1)
	{
		bIsMoving = false;
	}
}

void UPawnMoverComponent::AttemptMove(FVector MoveDirection)
{
	if (bIsMoving)
	{
		return;
	}

	CurrentLocation = MyOwner->GetActorLocation();
	TargetLocation = CurrentLocation + MoveDirection * MapDefaultsSubsystem->GetGridSnapValue();
	ElapsedDuration = 0;
	bIsMoving = true;
}

bool UPawnMoverComponent::CanMove()
{
	return !bIsMoving;
}
