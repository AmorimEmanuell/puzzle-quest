// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapConstructor.generated.h"

class UStaticMesh;
class AStaticMeshActor;

USTRUCT(BlueprintType)
struct FStaticMeshActorArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<AStaticMeshActor*> Array;

	AStaticMeshActor* operator[](size_t index)
	{
		return Array[index];
	}
};

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
	FVector GetGridPosition(int X, int Y);

private:
	UPROPERTY(EditAnywhere)
	FIntPoint DefaultMapSize{ 5, 5 };

	UPROPERTY(EditAnywhere)
	FIntPoint PlayerStart{ 0, 0 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> WhiteFloorTile;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> BlackFloorTile;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> WallTile;

	const float GridSnapValue{ 100 };

private:
	void ConstructFloorGrid(FIntPoint MapSize);
	void ConstructOuterWall(FIntPoint MapSize);
	AStaticMeshActor* SpawnMapActor(TSubclassOf<AStaticMeshActor> ActorBP, int X, int Y);

	void PlacePlayerOnStartPosition(FIntPoint StartPosition);
};
