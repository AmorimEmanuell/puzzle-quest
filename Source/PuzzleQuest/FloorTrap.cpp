// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTrap.h"
#include <Components/BoxComponent.h>

// Sets default values
AFloorTrap::AFloorTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFloorTrap::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorTrap::OverlapBegin);
}

void AFloorTrap::ActivateTrap()
{
	UE_LOG(LogTemp, Display, TEXT("AFloorTrap::ActivateTrap [%s]"), *GetName());
}

void AFloorTrap::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorldTimerManager().IsTimerActive(ActivationDelayTimerHandle))
	{
		UE_LOG(LogTemp, Display, TEXT("AFloorTrap::OverlapBegin [%s] TriggeringActor [%s]"), *GetName(), *OtherActor->GetName());
		GetWorldTimerManager().SetTimer(ActivationDelayTimerHandle, this, &AFloorTrap::ActivateTrap, ActivationDelay, false);
	}
}
