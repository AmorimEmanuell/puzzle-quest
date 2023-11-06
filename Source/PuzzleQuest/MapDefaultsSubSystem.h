// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MapDefaultsSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API UMapDefaultsSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	float GridSnapValue{ 100 };

public:
	float GetGridSnapValue() const { return GridSnapValue; };
	FVector GetGridPosition(int X, int Y);
};
