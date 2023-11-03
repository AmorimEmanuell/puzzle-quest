// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnMoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEQUEST_API UPawnMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AttemptMove(FVector MoveDirection);
	bool CanMove();

private:
	UPROPERTY(EditAnywhere)
	float MoveDistance{ 100 };

	UPROPERTY(EditAnywhere)
	float MovementDuration{ 0.25f };

	AActor* MyOwner;
	bool bIsMoving = false;
	FVector CurrentLocation;
	FVector TargetLocation;
	float ElapsedDuration;
};
