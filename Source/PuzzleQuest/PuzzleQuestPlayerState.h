// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PuzzleQuestPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API APuzzleQuestPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	FVector GridLocation;
};
