// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include <EnhancedInputComponent.h>
#include <Components/CapsuleComponent.h>
#include "Mover.h"
#include "CellChecker.h"
#include "Health.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Base Collision"));
	RootComponent = BaseCollision;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BaseCollision);

	NoseIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nose Indicator"));
	NoseIndicator->SetupAttachment(BaseMesh);

	Mover = CreateDefaultSubobject<UMover>(TEXT("Mover"));
	CellChecker = CreateDefaultSubobject<UCellChecker>(TEXT("CellChecker"));
	Health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	Health->OnHealthDepleted.BindUObject(this, &ABasePawn::Die);
}

void ABasePawn::Move(FVector MoveDirection)
{
	Mover->AttemptMove(MoveDirection);
}

void ABasePawn::Attack(UHealth* OtherHealth)
{
	UE_LOG(LogTemp, Error, TEXT("ABasePawn::Attack called! This should be overriden in inherited class"));
}

bool ABasePawn::CanAct()
{
	return TimeAfterLastAction >= DelayBetweenAction && Mover->CanMove();
}

void ABasePawn::PrepareCheckOnDirection(FVector Direction, float Modifier)
{
	Direction.Z = 0;
	Direction *= Modifier;
	Direction.Normalize();

	CellChecker->CheckCellOnDirection(Direction, this);
}

void ABasePawn::Die()
{
	UE_LOG(LogTemp, Error, TEXT("%s Died"), *GetName());
	Destroy();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

