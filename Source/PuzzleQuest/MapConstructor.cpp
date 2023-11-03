// Fill out your copyright notice in the Description page of Project Settings.


#include "MapConstructor.h"
#include <Engine/StaticMeshActor.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyPawn.h"

// Sets default values
AMapConstructor::AMapConstructor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapConstructor::BeginPlay()
{
	Super::BeginPlay();

	ConstructFloorGrid(DefaultMapSize);
	ConstructOuterWall(DefaultMapSize);
	PlacePlayerOnStartPosition(PlayerStart);
	SpawnEnemies(InitialEnemiesLocations);
}

// Called every frame
void AMapConstructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AMapConstructor::GetGridPosition(int X, int Y)
{
	return FVector{ X * GridSnapValue, Y * GridSnapValue, 0 };
}

void AMapConstructor::ConstructFloorGrid(FIntPoint MapSize)
{
	bool bBeginWithWhite = true;
	for (size_t i{ 0 }; i < MapSize.Y; i++)
	{
		bool bSwapTile = bBeginWithWhite;
		for (size_t j{ 0 }; j < MapSize.X; j++)
		{
			AStaticMeshActor* Tile = SpawnMapActor(bSwapTile ? BlackFloorTile : WhiteFloorTile, j, i);

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
		AStaticMeshActor* WallSouth = SpawnMapActor(WallTile, i, -1);
		AStaticMeshActor* WallNorth = SpawnMapActor(WallTile, i, MapSize.Y);

#if WITH_EDITOR
		WallSouth->SetFolderPath("/LevelLayout/OuterWalls/South");
		WallNorth->SetFolderPath("/LevelLayout/OuterWalls/North");
#endif
	}

	for (size_t i{ 0 }; i < MapSize.Y; i++)
	{
		AStaticMeshActor* WallEast = SpawnMapActor(WallTile, -1, i);
		AStaticMeshActor* WallWest = SpawnMapActor(WallTile, MapSize.X, i);

#if WITH_EDITOR
		WallEast->SetFolderPath("/LevelLayout/OuterWalls/East");
		WallWest->SetFolderPath("/LevelLayout/OuterWalls/West");
#endif
	}

	AStaticMeshActor* WallSouthEastCorner = SpawnMapActor(WallTile, -1, -1);
	AStaticMeshActor* WallSouthWestCorner = SpawnMapActor(WallTile, MapSize.X, -1);
	AStaticMeshActor* WallNorthEastCorner = SpawnMapActor(WallTile, -1, MapSize.Y);
	AStaticMeshActor* WallNorthWestCorner = SpawnMapActor(WallTile, MapSize.X, MapSize.Y);

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
		FVector ActorLocation = GetGridPosition(EnemyLocation.X, EnemyLocation.Y);
		GetWorld()->SpawnActor<AEnemyPawn>(EnemyPawn, ActorLocation, GetActorRotation());
	}
}

AStaticMeshActor* AMapConstructor::SpawnMapActor(TSubclassOf<AStaticMeshActor> ActorBP, int X, int Y)
{
	FVector ActorLocation = GetGridPosition(X, Y);
	AStaticMeshActor* Actor = GetWorld()->SpawnActor<AStaticMeshActor>(ActorBP, ActorLocation, GetActorRotation());
	return Actor;
}

void AMapConstructor::PlacePlayerOnStartPosition(FIntPoint StartPosition)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	PlayerLocation = GetGridPosition(StartPosition.X, StartPosition.Y);
	PlayerPawn->SetActorLocation(PlayerLocation);
}
