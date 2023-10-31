// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "Health.h"

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OverlapBegin);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(CurrentDirection * DeltaTime * CurrentSpeed);
}

void AFireBall::SetDirectionAndSpeed(FVector Direction, float Speed)
{
	CurrentDirection = Direction;
	CurrentSpeed = Speed;
}

void AFireBall::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Flame particles
	if (UHealth* Health = OtherActor->FindComponentByClass<UHealth>())
	{
		Health->TakeDamage(1);
	}

	Destroy();
}
