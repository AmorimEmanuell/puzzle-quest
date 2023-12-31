// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PathFindingSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FPathFindingData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FIntPoint Index{ -999, -999 };

	UPROPERTY(EditAnywhere)
	int32 CostToEnterTile{ 1 };

	UPROPERTY(EditAnywhere)
	int32 CostFromStart{ 999999 };

	UPROPERTY(EditAnywhere)
	int32 MinimumCostToTarget{ 999999 };

	UPROPERTY(EditAnywhere)
	FIntPoint PreviousIndex{ -999, -999 };
};

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API UPathFindingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	TArray<FIntPoint> FindPath(FIntPoint Start, FIntPoint Target);

private:
	FIntPoint StartIndex;
	FIntPoint TargetIndex;
	TMap<FIntPoint, bool> CurrentMapData;
	TArray<FIntPoint> DiscoveredTilesIndexes;
	TArray<int32> DiscoveredTilesSortingCosts;
	TArray<FIntPoint> AnalysedTilesIndexes;
	TMap<FIntPoint, FPathFindingData> PathFindingData;
	TArray<FPathFindingData> CurrentNeighbors;
	FPathFindingData CurrentNeighbor;

	void ClearData();
	bool IsInputValid(FIntPoint Start, FIntPoint Target);
	int32 GetMinimumCostBetweenTiles(FIntPoint Index1, FIntPoint Index2);
	void DiscoverTile(FPathFindingData TileData);
	void InsertTileInDiscoveredArray(FPathFindingData TileData);
	bool AnalyseNextDiscoveredTile();
	FPathFindingData GetCheapestTile();
	void GetValidNeighbors(FIntPoint TileIndex);
	void CreatePathFindingDataIfValid(FIntPoint TileIndex, FIntPoint PreviousIndex);
	bool DiscoverNextNeighbor(FPathFindingData CurrentDiscoveredTile);
	TArray<FIntPoint> GeneratePath();
};
