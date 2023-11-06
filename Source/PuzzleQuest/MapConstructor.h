// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapConstructor.generated.h"

USTRUCT()
struct FMapCellData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FIntPoint Index{ -999, -999 };

	UPROPERTY()
	bool bIsWalkable;
};

class UStaticMesh;
class AStaticMeshActor;
class AEnemyPawn;

UCLASS()
class PUZZLEQUEST_API AMapConstructor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapConstructor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	FIntPoint DefaultMapSize{ 5, 5 };

	UPROPERTY(EditAnywhere)
	FIntPoint PlayerStart{ 0, 0 };

	UPROPERTY(EditDefaultsOnly)
	TArray<FIntPoint> InitialEnemiesLocations;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> WhiteFloorTileBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> BlackFloorTileBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> WallTileBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyPawn> EnemyPawnBP;

	TMap<FIntPoint, bool> MapData;
	TObjectPtr<class UMapDefaultsSubSystem> MapDefaultsSubsytem;

	void ConstructFloorGrid(FIntPoint MapSize);
	void ConstructOuterWall(FIntPoint MapSize);
	void SpawnEnemies(TArray<FIntPoint> EnemiesLocations);
	AStaticMeshActor* SpawnMapActor(TSubclassOf<AStaticMeshActor> ActorBP, int X, int Y);
	void PlacePlayerOnStartPosition(FIntPoint StartPosition);
};
