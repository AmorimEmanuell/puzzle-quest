// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructor.h"
#include <Engine/StaticMeshActor.h>
#include <Kismet/GameplayStatics.h>
#include "BasePawn.h"
#include "EnemyPawn.h"
#include "MapDefaultsSubSystem.h"

// Sets default values
AMapConstructor::AMapConstructor()
{
}

// Called when the game starts or when spawned
void AMapConstructor::BeginPlay()
{
	Super::BeginPlay();

	MapDefaultsSubsytem = GetWorld()->GetGameInstance()->GetSubsystem<UMapDefaultsSubSystem>();

	ConstructFloorGrid(DefaultMapSize);
	ConstructOuterWall(DefaultMapSize);
	PlacePlayerOnStartPosition(PlayerStart);
	SpawnEnemies(InitialEnemiesLocations);

	MapDefaultsSubsytem->SetMapData(MapData);
	MapDefaultsSubsytem->SetCurrentMapSize(DefaultMapSize);
}

void AMapConstructor::ConstructFloorGrid(FIntPoint MapSize)
{
	bool bBeginWithWhite = true;
	for (int32 i{ 0 }; i < MapSize.Y; i++)
	{
		bool bSwapTile = bBeginWithWhite;
		for (int32 j{ 0 }; j < MapSize.X; j++)
		{
			AStaticMeshActor* Tile = SpawnMapActor(bSwapTile ? BlackFloorTileBP : WhiteFloorTileBP, j, i);
			MapData.Add({ j, i }, true);

#if WITH_EDITOR
			FString Path = FString::Printf(TEXT("/LevelLayout/FloorTiles/Row%d"), i);
			Tile->SetFolderPath(*Path);
#endif

			bSwapTile = !bSwapTile;
		}

		bBeginWithWhite = !bBeginWithWhite;
	}
}

void AMapConstructor::ConstructOuterWall(FIntPoint MapSize)
{
	for (size_t i{ 0 }; i < MapSize.X; i++)
	{
		AStaticMeshActor* WallSouth = SpawnMapActor(WallTileBP, i, -1);
		AStaticMeshActor* WallNorth = SpawnMapActor(WallTileBP, i, MapSize.Y);

#if WITH_EDITOR
		WallSouth->SetFolderPath("/LevelLayout/OuterWalls/South");
		WallNorth->SetFolderPath("/LevelLayout/OuterWalls/North");
#endif
	}

	for (size_t i{ 0 }; i < MapSize.Y; i++)
	{
		AStaticMeshActor* WallEast = SpawnMapActor(WallTileBP, -1, i);
		AStaticMeshActor* WallWest = SpawnMapActor(WallTileBP, MapSize.X, i);

#if WITH_EDITOR
		WallEast->SetFolderPath("/LevelLayout/OuterWalls/East");
		WallWest->SetFolderPath("/LevelLayout/OuterWalls/West");
#endif
	}

	AStaticMeshActor* WallSouthEastCorner = SpawnMapActor(WallTileBP, -1, -1);
	AStaticMeshActor* WallSouthWestCorner = SpawnMapActor(WallTileBP, MapSize.X, -1);
	AStaticMeshActor* WallNorthEastCorner = SpawnMapActor(WallTileBP, -1, MapSize.Y);
	AStaticMeshActor* WallNorthWestCorner = SpawnMapActor(WallTileBP, MapSize.X, MapSize.Y);

#if WITH_EDITOR
	WallSouthEastCorner->SetFolderPath("/LevelLayout/OuterWalls/Corners");
	WallSouthWestCorner->SetFolderPath("/LevelLayout/OuterWalls/Corners");
	WallNorthEastCorner->SetFolderPath("/LevelLayout/OuterWalls/Corners");
	WallNorthWestCorner->SetFolderPath("/LevelLayout/OuterWalls/Corners");
#endif
}

void AMapConstructor::SpawnEnemies(TArray<FIntPoint> EnemiesLocations)
{
	for (FIntPoint EnemyLocation : EnemiesLocations)
	{
		FVector ActorLocation = MapDefaultsSubsytem->GetGridPosition(EnemyLocation.X, EnemyLocation.Y);
		TObjectPtr<AEnemyPawn> EnemyPawn = GetWorld()->SpawnActor<AEnemyPawn>(EnemyPawnBP, ActorLocation, GetActorRotation());
		EnemyPawn->SetupGridLocation(EnemyLocation);
	}
}

AStaticMeshActor* AMapConstructor::SpawnMapActor(TSubclassOf<AStaticMeshActor> ActorBP, int X, int Y)
{
	FVector ActorLocation = MapDefaultsSubsytem->GetGridPosition(X, Y);
	AStaticMeshActor* Actor = GetWorld()->SpawnActor<AStaticMeshActor>(ActorBP, ActorLocation, GetActorRotation());
	return Actor;
}

void AMapConstructor::PlacePlayerOnStartPosition(FIntPoint StartPosition)
{
	TObjectPtr<ABasePawn> PlayerPawn = Cast<ABasePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	FVector PlayerLocation = MapDefaultsSubsytem->GetGridPosition(StartPosition.X, StartPosition.Y);
	PlayerPawn->SetActorLocation(PlayerLocation);
	PlayerPawn->SetupGridLocation(StartPosition);
}
