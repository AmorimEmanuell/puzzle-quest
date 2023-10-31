// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloorTrap.h"
#include "SpikeTrap.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEQUEST_API ASpikeTrap : public AFloorTrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpikeTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ActivateTrap() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SpikesMesh;

	UPROPERTY(EditAnywhere)
	FVector SpikeOffset{ 0, 0, 20 };

	UPROPERTY(EditAnywhere)
	float SpikeVelocity{ 10 };

	UPROPERTY(EditAnywhere)
	float ActiveDuration{ 2 };

	bool bIsTrapActivated;
	FVector InitialSpikeLocation;
	FVector TargetSpikeLocation;
	FTimerHandle ReturnSpikesTimerHandle;

	UFUNCTION()
	void CheckForDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void MoveSpikeToTarget(FVector TargetLocation, float DeltaTime);
	void DeactivateTrap();
};
