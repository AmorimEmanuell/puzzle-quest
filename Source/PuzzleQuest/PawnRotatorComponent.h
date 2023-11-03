// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnRotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEQUEST_API UPawnRotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnRotatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RotateTo(FVector Direction);

private:
	UPROPERTY(EditAnywhere)
	float RotateDuration{ 0.1f };

	AActor* MyOwner;
	bool bIsRotating = false;
	FRotator CurrentRotation;
	FRotator TargetRotation;
	float ElapsedDuration;
};
