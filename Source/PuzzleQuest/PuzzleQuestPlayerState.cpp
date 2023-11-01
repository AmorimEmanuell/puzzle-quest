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
