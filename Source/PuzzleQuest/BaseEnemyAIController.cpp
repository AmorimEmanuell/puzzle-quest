// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyPawn.h"
#include <Kismet/KismetMathLibrary.h>
#include "PathFindingSubsystem.h"
#include "MapDefaultsSubSystem.h"

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
	TObjectPtr<AEnemyPawn> MyPawn = Cast<AEnemyPawn>(GetPawn());
	FIntPoint PatrolLocation = MyPawn->GetPatrolLocation();
	int32 PatrolRange = MyPawn->GetPatrolRange();
	TObjectPtr<UMapDefaultsSubSystem> MapDefaultsSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMapDefaultsSubSystem>();
	FIntPoint CurrentMapSize = MapDefaultsSubsystem->GetCurrentMapSize();
	FIntPoint TargetLocation = CalculateTargetLocation(PatrolLocation, PatrolRange, CurrentMapSize);

	TObjectPtr<UPathFindingSubsystem> PathFindingSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPathFindingSubsystem>();
	CurrentPath = PathFindingSubsystem->FindPath(MyPawn->GetGridLocation(), TargetLocation);
	if (CurrentPath.Num() > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Found path for [%s]"), *MyPawn->GetName());
		for (FIntPoint Point : CurrentPath)
		{
			UE_LOG(LogTemp, Display, TEXT("%s"), *Point.ToString());
		}

		GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::MoveToNextLocationOnPath, GetThinkingDelay(), false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find path for [%s] Start: %s Target: %s"), *MyPawn->GetName(), *MyPawn->GetGridLocation().ToString(), *TargetLocation.ToString());
		GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::DecideNextLocation, GetThinkingDelay(), false);
	}
}

FIntPoint ABaseEnemyAIController::CalculateTargetLocation(FIntPoint PatrolLocation, int32 PatrolRange, FIntPoint MapSize) const
{
	int32 X = FMath::RandRange(FMath::Clamp(PatrolLocation.X - PatrolRange, 0, MapSize.X), FMath::Clamp(PatrolLocation.X + PatrolRange, 0, MapSize.X));
	int32 Y = FMath::RandRange(FMath::Clamp(PatrolLocation.Y - PatrolRange, 0, MapSize.Y), FMath::Clamp(PatrolLocation.Y + PatrolRange, 0, MapSize.Y));
	return FIntPoint{ X, Y };
}

void ABaseEnemyAIController::MoveToNextLocationOnPath()
{
	TObjectPtr<AEnemyPawn> MyPawn = Cast<AEnemyPawn>(GetPawn());
	FIntPoint CurrentLocation = MyPawn->GetGridLocation();
	FIntPoint NextLocation = CurrentPath[0];

	FVector MoveDirection { NextLocation - CurrentLocation, 0 };
	TObjectPtr<AActor> FoundActor = MyPawn->CheckCellOnDirection(MoveDirection);
	if (FoundActor == nullptr)
	{
		MyPawn->MoveIn(MoveDirection);
		MyPawn->RotateTo(MoveDirection);
		CurrentPath.RemoveAt(0);
	}

	if (CurrentPath.Num() > 0)
	{
		GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::MoveToNextLocationOnPath, GetThinkingDelay(), false);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Arrived at destination. Looking for next path..."), *MyPawn->GetName());
		GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::DecideNextLocation, GetThinkingDelay(), false);
	}
}
