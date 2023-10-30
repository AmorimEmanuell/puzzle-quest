// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleQuestGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "SaveData.h"

void UPuzzleQuestGameInstance::OnStart()
{
    Super::OnStart();

    if (SaveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot("Default", 0)))
    {
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        UE_LOG(LogTemp, Warning, TEXT("LOADED SAVE DATA: KnightAtkPower: %d, KnightStamina: %d, KnightMaxHealth: %d"), SaveData->PlayerStats.KnightAtkPower, SaveData->PlayerStats.KnightStamina, SaveData->PlayerStats.KnightMaxHealth);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NO SAVE DATA FOUND. CREATING..."));

        SaveData = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));
        if (SaveData)
        {
            if (UGameplayStatics::SaveGameToSlot(SaveData, "Default", 0))
            {
                // Save succeeded.
                UE_LOG(LogTemp, Error, TEXT("SAVE DATA CREATED SUCCESSFULLY"));
            }
        }
    }
}

FPlayerStats UPuzzleQuestGameInstance::GetPlayerStats()
{
    if (SaveData)
    {
        return SaveData->PlayerStats;
    }

    return FPlayerStats();
}
