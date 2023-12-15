// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFindingSubsystem.h"
#include "MapDefaultsSubSystem.h"
#include <Algo/Reverse.h>

TArray<FIntPoint> UPathFindingSubsystem::FindPath(FIntPoint Start, FIntPoint Target)
{
	TObjectPtr<UMapDefaultsSubSystem> MapDefaultsSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMapDefaultsSubSystem>();
	CurrentMapData = MapDefaultsSubsystem->GetMapData();

	StartIndex = Start;
	TargetIndex = Target;

	ClearData();

	if (IsInputValid(Start, Target))
	{
		FPathFindingData TileData{ Start, 1, 0, GetMinimumCostBetweenTiles(Start, Target) };
		DiscoverTile(TileData);

		while (DiscoveredTilesIndexes.Num() > 0)
		{
			if (AnalyseNextDiscoveredTile())
			{
				return GeneratePath();
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("UPathFindingSubsystem::FindPath Unable to find path between Start %s and Target %s"), *Start.ToString(), *Target.ToString());
	return TArray<FIntPoint>();
}

void UPathFindingSubsystem::ClearData()
{
	PathFindingData.Reset();
	DiscoveredTilesIndexes.Reset();
	DiscoveredTilesSortingCosts.Reset();
	AnalysedTilesIndexes.Reset();
	CurrentNeighbors.Reset();
}

bool UPathFindingSubsystem::IsInputValid(FIntPoint Start, FIntPoint Target)
{
	if (Start == Target)
	{
		return false;
	}

	if (!CurrentMapData.Contains(Start) || !CurrentMapData[Start])
	{
		UE_LOG(LogTemp, Error, TEXT("UPathFindingSubsystem::IsInputValid Start %s is invalid!"), *Start.ToString());
		return false;
	}

	if (!CurrentMapData.Contains(Start) || !CurrentMapData[Start])
	{
		UE_LOG(LogTemp, Error, TEXT("UPathFindingSubsystem::IsInputValid Target %s is invalid!"), *Target.ToString());
		return false;
	}

	return true;
}

int32 UPathFindingSubsystem::GetMinimumCostBetweenTiles(FIntPoint Index1, FIntPoint Index2)
{
	FIntPoint Sub = Index1 - Index2;
	return FMath::Abs(Sub.X) + FMath::Abs(Sub.Y);
}

void UPathFindingSubsystem::DiscoverTile(FPathFindingData TileData)
{
	PathFindingData.Add(TileData.Index, TileData);
	InsertTileInDiscoveredArray(TileData);
}

void UPathFindingSubsystem::InsertTileInDiscoveredArray(FPathFindingData TileData)
{
	int32 SortingCost = TileData.CostFromStart + TileData.MinimumCostToTarget;
	if (DiscoveredTilesSortingCosts.Num() == 0)
	{
		DiscoveredTilesSortingCosts.Add(SortingCost);
		DiscoveredTilesIndexes.Add(TileData.Index);
	}
	else
	{
		if (SortingCost >= DiscoveredTilesSortingCosts.Last())
		{
			DiscoveredTilesSortingCosts.Add(SortingCost);
			DiscoveredTilesIndexes.Add(TileData.Index);
		}
		else
		{
			for (int32 i{ 0 }; i < DiscoveredTilesSortingCosts.Num(); i++)
			{
				if (DiscoveredTilesSortingCosts[i] >= SortingCost)
				{
					DiscoveredTilesSortingCosts.Insert(SortingCost, i);
					DiscoveredTilesIndexes.Insert(TileData.Index, i);
					break;
				}
			}
		}
	}
}

bool UPathFindingSubsystem::AnalyseNextDiscoveredTile()
{
	FPathFindingData CurrentDiscoveredTile = GetCheapestTile();
	GetValidNeighbors(CurrentDiscoveredTile.Index);

	while (CurrentNeighbors.Num() > 0)
	{
		if (DiscoverNextNeighbor(CurrentDiscoveredTile))
		{
			return true;
		}
	}

	return false;
}

FPathFindingData UPathFindingSubsystem::GetCheapestTile()
{
	FIntPoint TileIndex = DiscoveredTilesIndexes[0];
	DiscoveredTilesIndexes.RemoveAt(0);
	DiscoveredTilesSortingCosts.RemoveAt(0);
	AnalysedTilesIndexes.Add(TileIndex);
	return PathFindingData[TileIndex];
}

void UPathFindingSubsystem::GetValidNeighbors(FIntPoint TileIndex)
{
	FIntPoint Left{ TileIndex.X - 1, TileIndex.Y };
	CreatePathFindingDataIfValid(Left, TileIndex);

	FIntPoint Right{ TileIndex.X + 1, TileIndex.Y };
	CreatePathFindingDataIfValid(Right, TileIndex);

	FIntPoint Up{ TileIndex.X, TileIndex.Y + 1 };
	CreatePathFindingDataIfValid(Up, TileIndex);

	FIntPoint Down{ TileIndex.X, TileIndex.Y - 1 };
	CreatePathFindingDataIfValid(Down, TileIndex);
}

void UPathFindingSubsystem::CreatePathFindingDataIfValid(FIntPoint TileIndex, FIntPoint PreviousIndex)
{
	if (CurrentMapData.Contains(TileIndex) && CurrentMapData[TileIndex])
	{
		FPathFindingData NewPathFindingData;
		NewPathFindingData.Index = TileIndex;
		NewPathFindingData.PreviousIndex = PreviousIndex;
		CurrentNeighbors.Add(NewPathFindingData);
	}
}

bool UPathFindingSubsystem::DiscoverNextNeighbor(FPathFindingData CurrentDiscoveredTile)
{
	CurrentNeighbor = CurrentNeighbors[0];
	CurrentNeighbors.RemoveAt(0);

	if (!AnalysedTilesIndexes.Contains(CurrentNeighbor.Index))
	{
		int32 CostFromStart = CurrentDiscoveredTile.CostFromStart + CurrentNeighbor.CostToEnterTile;
		int32 IndexInDiscovered = DiscoveredTilesIndexes.Find(CurrentNeighbor.Index);
		if (IndexInDiscovered == INDEX_NONE)
		{
			DiscoverTile(FPathFindingData{ CurrentNeighbor.Index, CurrentNeighbor.CostToEnterTile, CostFromStart, GetMinimumCostBetweenTiles(CurrentNeighbor.Index, TargetIndex), CurrentDiscoveredTile.Index });
		}
		else
		{
			CurrentNeighbor = PathFindingData[CurrentNeighbor.Index];
			if (CostFromStart < CurrentNeighbor.CostFromStart)
			{
				DiscoveredTilesIndexes.RemoveAt(IndexInDiscovered);
				DiscoveredTilesSortingCosts.RemoveAt(IndexInDiscovered);

				DiscoverTile(FPathFindingData{ CurrentNeighbor.Index, CurrentNeighbor.CostToEnterTile, CostFromStart, GetMinimumCostBetweenTiles(CurrentNeighbor.Index, TargetIndex), CurrentDiscoveredTile.Index });
			}
			else
			{
				return false;
			}
		}
	}

	return CurrentNeighbor.Index == TargetIndex;
}

TArray<FIntPoint> UPathFindingSubsystem::GeneratePath()
{
	TArray<FIntPoint> InversedPath;
	FIntPoint Current = TargetIndex;
	while (Current != StartIndex)
	{
		InversedPath.Add(Current);

		FPathFindingData TileData = PathFindingData[Current];
		Current = TileData.PreviousIndex;
	}

	Algo::Reverse(InversedPath);

	/*TArray<FIntPoint> FinalPath;
	for (int32 i{ InversedPath.Num() - 1 }; i >= 0; i--)
	{
		FinalPath.Add(InversedPath[i]);
	}*/

	return InversedPath;
}
