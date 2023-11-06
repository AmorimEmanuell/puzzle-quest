// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyPawn.h"
#include <Kismet/KismetMathLibrary.h>
#include "PathFindingSubsystem.h"

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
	UE_LOG(LogTemp, Error, TEXT("ABaseEnemyAIController::DecideNextLocation"));
	UPathFindingSubsystem* PathFindingSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPathFindingSubsystem>();
	AEnemyPawn* MyPawn = Cast<AEnemyPawn>(GetPawn());
	TArray<FIntPoint> Path = PathFindingSubsystem->FindPath(MyPawn->GetGridLocation(), FIntPoint{0, 0});

	for (FIntPoint point : Path)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *point.ToString());
	}

	/*for (FVector& Direction : CheckDirections)
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
	GetWorldTimerManager().SetTimer(PatrolTimeHandle, this, &ABaseEnemyAIController::DecideNextLocation, GetThinkingDelay(), false);*/
}
