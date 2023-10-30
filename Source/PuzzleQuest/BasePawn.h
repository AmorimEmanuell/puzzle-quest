// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UMover;
class UCellChecker;
class UHealth;
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

	void Move(FVector MoveDirection);

	virtual void Attack(UHealth* OtherHealth);

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* BaseCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UMover* Mover;

	UPROPERTY(VisibleAnywhere)
	UCellChecker* CellChecker;

	UPROPERTY(VisibleAnywhere)
	UHealth* Health;

	bool CanAct();
	void PrepareCheckOnDirection(FVector Direction, float Modifier);

public:
	UFUNCTION()
	void Die();
};
