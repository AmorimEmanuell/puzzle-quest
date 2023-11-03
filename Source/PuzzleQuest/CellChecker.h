// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "CellChecker.generated.h"

class ABasePawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEQUEST_API UCellChecker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCellChecker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	AActor* CheckCellOnDirection(FVector Direction);

private:
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditAnywhere)
	float CheckDistance{ 100 };

	UPROPERTY(EditAnywhere)
	float HeightCheck{ 25 };
};
