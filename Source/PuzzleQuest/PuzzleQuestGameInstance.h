// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleQuestGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API UPuzzleQuestGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void OnStart() override;

	struct FPlayerStats GetPlayerStats();

private:
	class USaveData* SaveData;
};
