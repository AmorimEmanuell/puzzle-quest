// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBallShooter.generated.h"

UCLASS()
class PUZZLEQUEST_API AFireBallShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBallShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Barrel;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* FireBallSpawnLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFireBall> FireBallBP;

	UPROPERTY(EditAnywhere)
	float FireRate{ 2 };

	UPROPERTY(EditAnywhere)
	float FireBallSpeed{ 200 };

	float TimeSinceLastFireBall;
};
