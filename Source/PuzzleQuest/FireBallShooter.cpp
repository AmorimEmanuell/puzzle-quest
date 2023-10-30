// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBallShooter.h"
#include <Engine/StaticMeshActor.h>
#include "FireBall.h"

// Sets default values
AFireBallShooter::AFireBallShooter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	Barrel->SetupAttachment(RootComponent);

	FireBallSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireBallSpawnLocation"));
	FireBallSpawnLocation->SetupAttachment(Barrel);
}

// Called when the game starts or when spawned
void AFireBallShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireBallShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastFireBall += DeltaTime;
	if (TimeSinceLastFireBall >= FireRate)
	{
		TimeSinceLastFireBall = 0;
		AFireBall* FireBall = GetWorld()->SpawnActor<AFireBall>(FireBallBP, FireBallSpawnLocation->GetComponentLocation(), FireBallSpawnLocation->GetComponentRotation());
		FireBall->SetDirectionAndSpeed(GetActorForwardVector(), FireBallSpeed);
	}
}
