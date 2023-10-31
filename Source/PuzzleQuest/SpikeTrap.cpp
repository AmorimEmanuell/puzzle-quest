// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"
#include "Health.h"

ASpikeTrap::ASpikeTrap()
{
	SpikesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikesMesh"));
	SpikesMesh->SetupAttachment(RootComponent);
}

void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	SpikesMesh->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::CheckForDamage);
	InitialSpikeLocation = SpikesMesh->GetRelativeLocation();
	TargetSpikeLocation = InitialSpikeLocation + SpikeOffset;
}

void ASpikeTrap::ActivateTrap()
{
	Super::ActivateTrap();

	bIsTrapActivated = true;
}

void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTrapActivated)
	{
		MoveSpikeToTarget(TargetSpikeLocation, DeltaTime);
	}
	else
	{
		MoveSpikeToTarget(InitialSpikeLocation, DeltaTime);
	}
}

void ASpikeTrap::CheckForDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("ASpikeTrap::CheckForDamage [%s] TriggeringActor [%s]"), *GetName(), *OtherActor->GetName());

	if (IsValid(OtherActor))
	{
		if (UHealth* Health = OtherActor->FindComponentByClass<UHealth>())
		{
			Health->TakeDamage(1);
		}
	}
}

void ASpikeTrap::MoveSpikeToTarget(FVector TargetLocation, float DeltaTime)
{
	FVector NextLocation = FMath::VInterpConstantTo(SpikesMesh->GetRelativeLocation(), TargetLocation, DeltaTime, SpikeVelocity);
	double Distance = FVector::Distance(NextLocation, SpikesMesh->GetRelativeLocation());
	if (FMath::IsNearlyZero(Distance) && bIsTrapActivated)
	{
		if (!GetWorldTimerManager().IsTimerActive(ReturnSpikesTimerHandle))
		{
			GetWorldTimerManager().SetTimer(ReturnSpikesTimerHandle, this, &ASpikeTrap::DeactivateTrap, 1, false);
		}

		return;
	}

	SpikesMesh->SetRelativeLocation(NextLocation);
}

void ASpikeTrap::DeactivateTrap()
{
	UE_LOG(LogTemp, Display, TEXT("ASpikeTrap::DeactivateTrap [%s]"), *GetName());
	bIsTrapActivated = false;
}
