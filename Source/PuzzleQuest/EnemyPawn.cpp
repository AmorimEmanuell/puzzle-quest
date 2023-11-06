// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

void AEnemyPawn::OnInteract(ABasePawn* Pawn)
{
	Pawn->Attack(Health);
}

FIntPoint AEnemyPawn::GetPatrolLocation() const
{
	return StartGridLocation;
}

int32 AEnemyPawn::GetPatrolRange() const
{
	return PatrolRange;
}
