// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include <EnhancedInputComponent.h>
#include <Components/CapsuleComponent.h>
#include "CellChecker.h"
#include "Health.h"
#include "PawnRotatorComponent.h"
#include "PawnMoverComponent.h"
#include "Interactable.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	NoseIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nose Indicator"));
	NoseIndicator->SetupAttachment(BaseMesh);

	BaseCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Base Collision"));
	BaseCollision->SetupAttachment(RootComponent);

	CellChecker = CreateDefaultSubobject<UCellChecker>(TEXT("CellChecker"));
	Health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
	PawnRotator = CreateDefaultSubobject<UPawnRotatorComponent>(TEXT("PawnRotator"));
	PawnMover = CreateDefaultSubobject<UPawnMoverComponent>(TEXT("PawnMover"));
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	Health->OnHealthDepleted.BindUObject(this, &ABasePawn::Die);
}

void ABasePawn::MoveIn(FVector MoveDirection)
{
	PawnMover->AttemptMove(MoveDirection);
	UpdateGridLocation(FIntPoint{ CurrentGridLocation.X + (int32)MoveDirection.X, CurrentGridLocation.Y + (int32)MoveDirection.Y });
}

void ABasePawn::RotateTo(FVector RotateDirection)
{
	PawnRotator->RotateTo(RotateDirection);
}

void ABasePawn::Attack(UHealth* OtherHealth)
{
	UE_LOG(LogTemp, Error, TEXT("ABasePawn::Attack called! This should be overriden in inherited class"));
}

bool ABasePawn::CanAct()
{
	return TimeAfterLastAction >= DelayBetweenAction && PawnMover->CanMove();
}

AActor* ABasePawn::CheckCellOnDirection(FVector Direction)
{
	return CellChecker->CheckCellOnDirection(Direction);
}

FVector ABasePawn::GetCheckDirection(FVector Direction, float Modifier) const
{
	Direction.Z = 0;
	Direction *= Modifier;
	Direction.Normalize();
	return Direction;
}

void ABasePawn::SetupGridLocation(FIntPoint GridLocation)
{
	StartGridLocation = GridLocation;
	CurrentGridLocation = GridLocation;
}

void ABasePawn::UpdateGridLocation(FIntPoint GridLocation)
{
	CurrentGridLocation = GridLocation;
}

FIntPoint ABasePawn::GetGridLocation() const
{
	return CurrentGridLocation;
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
