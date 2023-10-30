// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

void AEnemyPawn::OnInteract(ABasePawn* Pawn)
{
	UE_LOG(LogTemp, Error, TEXT("AEnemyPawn::OnInteract: %s"), *GetName());
	Pawn->Attack(Health);
}
