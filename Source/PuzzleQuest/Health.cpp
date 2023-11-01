// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::TakeDamage(uint8 Damage)
{
	if (CurrentHealth <= 0)
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("%s TakeDamage: %d"), *GetOwner()->GetName(), Damage);
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0)
	{
		OnHealthDepleted.ExecuteIfBound();
	}
}
