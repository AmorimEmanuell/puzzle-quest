// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UMover;
class UCellChecker;
class UHealth;
class UPawnRotatorComponent;
class UPawnMoverComponent;
struct FInputActionValue;

UCLASS()
class PUZZLEQUEST_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveIn(FVector MoveDirection);
	void RotateTo(FVector RotateDirection);

	virtual void Attack(UHealth* OtherHealth);
	AActor* CheckCellOnDirection(FVector Direction);

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* BaseCollision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* NoseIndicator;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnMoverComponent> PawnMover;

	UPROPERTY(VisibleAnywhere)
	UCellChecker* CellChecker;

	UPROPERTY(VisibleAnywhere)
	UHealth* Health;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnRotatorComponent> PawnRotator;

	UPROPERTY(EditAnywhere)
	float DelayBetweenAction{ 0.2f };

	UPROPERTY(VisibleInstanceOnly)
	FIntPoint CurrentGridLocation;

	float TimeAfterLastAction;
	FIntPoint StartGridLocation;

	bool CanAct();
	FVector GetCheckDirection(FVector Direction, float Modifier = 1) const;

public:
	void SetupGridLocation(FIntPoint GridLocation);
	void UpdateGridLocation(FIntPoint GridLocation);
	FIntPoint GetGridLocation() const;

	UFUNCTION()
	void Die();
};
