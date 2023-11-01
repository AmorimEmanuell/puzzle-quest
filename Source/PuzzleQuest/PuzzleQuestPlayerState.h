// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SaveData.h"
#include "PuzzleQuestPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API APuzzleQuestPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FPlayerStats& GetPlayerStats();

private:
	FPlayerStats PlayerStats;
};
