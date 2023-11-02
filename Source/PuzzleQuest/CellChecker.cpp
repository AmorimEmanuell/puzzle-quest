// Fill out your copyright notice in the Description page of Project Settings.


#include "CellChecker.h"
#include "BasePawn.h"
#include "Health.h"
#include "Interactable.h"

// Sets default values for this component's properties
UCellChecker::UCellChecker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UCellChecker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UCellChecker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCellChecker::CheckCellOnDirection(FVector Direction, ABasePawn* Pawn)
{
	FHitResult Hit;
	FVector TraceStart = GetOwner()->GetActorLocation() + FVector::UpVector * HeightCheck;
	FVector TraceEnd = TraceStart + Direction * CheckDistance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	FCollisionObjectQueryParams ObjectQueryParams{ ObjectTypes };
	GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectQueryParams, CollisionQueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 1.0f, 0, 5.0f);

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		if (IInteractable* Interactable = Cast<IInteractable>(Hit.GetActor()))
		{
			Interactable->OnInteract(Pawn);
		}
	}
	else
	{
		Pawn->Move(Direction);
	}
}
