// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SaveData.h"
#include "PuzzleQuestPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStaminaChangedSignature, FPlayerStats, PlayerStats);
/**
 * 
 */
UCLASS(BlueprintType)
class PUZZLEQUEST_API APuzzleQuestPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FStaminaChangedSignature OnStatsChanged;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FPlayerStats& GetPlayerStats();

	bool ConsumeStamina();
	uint8 GetAttackPower();

private:
	FPlayerStats PlayerStats;
};
