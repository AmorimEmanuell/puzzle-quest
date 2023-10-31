// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTrap.generated.h"

UCLASS()
class PUZZLEQUEST_API AFloorTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ActivateTrap();

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere)
	float ActivationDelay{ 1 };

	FTimerHandle ActivationDelayTimerHandle;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
