// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEQUEST_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AttemptMove(FVector MoveDirection);
	bool CanMove();

private:
	AActor* MyOwner;

	bool IsMoving = false;

	FVector CurrentLocation;
	FVector TargetLocation;
	float ElapsedMovementDuration;

	FRotator CurrentRotation;
	FRotator TargetRotation;
	float ElapsedRotateDuration;

	UPROPERTY(EditAnywhere)
	float MoveDistance{ 100 };

	UPROPERTY(EditAnywhere)
	float MovementDuration{ 0.25f };

	UPROPERTY(EditAnywhere)
	float RotateDuration{ 0.1f };
};
