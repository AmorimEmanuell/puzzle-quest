// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 KnightAtkPower{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 KnightStamina{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 KnightMaxHealth{ 1 };

	void SpendStamina()
	{
		KnightStamina--;
	}
};

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API USaveData : public ULocalPlayerSaveGame
{
	GENERATED_BODY()

public:
	FPlayerStats PlayerStats;
};
