// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseEnemyAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere)
	FVector2D ThinkingDelayRange{ 2.0f, 4.0f };

	FTimerHandle PatrolTimeHandle;
	TArray<FIntPoint> CurrentPath;

	void DecideNextLocation();
	float GetThinkingDelay() { return FMath::RandRange(ThinkingDelayRange.X, ThinkingDelayRange.Y); };
	FIntPoint CalculateTargetLocation(FIntPoint PatrolLocation, int32 PatrolRange, FIntPoint MapSize) const;
	void MoveToNextLocationOnPath();
};
