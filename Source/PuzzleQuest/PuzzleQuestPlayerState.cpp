// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleQuestPlayerState.h"
#include "PuzzleQuestGameInstance.h"
#include <Kismet/GameplayStatics.h>

void APuzzleQuestPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (UPuzzleQuestGameInstance* GameInstance = Cast<UPuzzleQuestGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		PlayerStats = GameInstance->GetPlayerStats();
	}
}

FPlayerStats& APuzzleQuestPlayerState::GetPlayerStats()
{
	return PlayerStats;
}

bool APuzzleQuestPlayerState::ConsumeStamina()
{
	if (PlayerStats.KnightStamina > 0)
	{
		PlayerStats.SpendStamina();
		OnStatsChanged.Broadcast(PlayerStats);
		return true;
	}

	UE_LOG(LogTemp, Display, TEXT("NO STAMINA!"));
	return false;
}

uint8 APuzzleQuestPlayerState::GetAttackPower()
{
	return PlayerStats.KnightAtkPower;
}
