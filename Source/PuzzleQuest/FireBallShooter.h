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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Barrel;

	UPROPERTY(EditAnywhere)
	USceneComponent* FireBallSpawnLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFireBall> FireBallBP;

	UPROPERTY(EditAnywhere)
	float FireRate{ 2 };

	UPROPERTY(EditAnywhere)
	float FireBallSpeed{ 200 };

	float TimeSinceLastFireBall;
};
