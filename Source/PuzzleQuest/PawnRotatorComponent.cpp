// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnRotatorComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UPawnRotatorComponent::UPawnRotatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPawnRotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = GetOwner();
}

// Called every frame
void UPawnRotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsRotating)
	{
		return;
	}

	ElapsedDuration += DeltaTime;
	float Alpha = FMath::Clamp(ElapsedDuration / RotateDuration, 0, 1);
	FRotator StepRotation = FMath::Lerp(CurrentRotation, TargetRotation, Alpha);
	MyOwner->SetActorRotation(StepRotation);

	if (Alpha == 1)
	{
		bIsRotating = false;
	}
}

void UPawnRotatorComponent::RotateTo(FVector Direction)
{
	CurrentRotation = MyOwner->GetActorRotation();
	TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	ElapsedDuration = 0;
	bIsRotating = true;
}
