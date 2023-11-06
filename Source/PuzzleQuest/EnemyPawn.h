// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Interactable.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API AEnemyPawn : public ABasePawn, public IInteractable
{
	GENERATED_BODY()

public:
	virtual void OnInteract(ABasePawn* Pawn) override;
	FIntPoint GetPatrolLocation() const;
	int32 GetPatrolRange() const;

private:
	UPROPERTY(EditAnywhere)
	int32 PatrolRange{ 3 };
};
