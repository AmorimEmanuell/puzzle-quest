// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BasePawn.h"
#include <Kismet/KismetMathLibrary.h>

ABaseEnemyAIController::ABaseEnemyAIController()
{
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::DecideNextLocation, GetThinkingDelay(), false);
}

void ABaseEnemyAIController::DecideNextLocation()
{
	ABasePawn* MyPawn = Cast<ABasePawn>(GetPawn());
	for (FVector& Direction : CheckDirections)
	{
		AActor* FoundActor = MyPawn->CheckCellOnDirection(Direction);
		if (FoundActor == nullptr)
		{
			AvailableDirections.Add(Direction);
		}
	}

	int32 SelectedIndex = FMath::RandRange(0, AvailableDirections.Num() - 1);
	MyPawn->MoveIn(AvailableDirections[SelectedIndex]);
	MyPawn->RotateTo(AvailableDirections[SelectedIndex]);
	AvailableDirections.Reset();
	GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::DecideNextLocation, GetThinkingDelay(), false);
}
