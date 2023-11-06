// Fill out your copyright notice in the Description page of Project Settings.


#include "MapDefaultsSubSystem.h"

FVector UMapDefaultsSubSystem::GetGridPosition(int X, int Y)
{
	return FVector{ X * GridSnapValue, Y * GridSnapValue, 0 };
}
