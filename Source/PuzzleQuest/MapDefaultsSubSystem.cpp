// Fill out your copyright notice in the Description page of Project Settings.


#include "MapDefaultsSubSystem.h"

FVector UMapDefaultsSubSystem::GetGridPosition(int X, int Y)
{
	return FVector{ X * GridSnapValue, Y * GridSnapValue, 0 };
}

void UMapDefaultsSubSystem::SetCurrentMapSize(FIntPoint MapSize)
{
	CurrentMapSize = MapSize;
}

FIntPoint UMapDefaultsSubSystem::GetCurrentMapSize() const
{
	return CurrentMapSize;
}

void UMapDefaultsSubSystem::SetMapData(TMap<FIntPoint, bool> MapData)
{
	CurrentMapData = MapData;
}

TMap<FIntPoint, bool> UMapDefaultsSubSystem::GetMapData() const
{
	return CurrentMapData;
}
