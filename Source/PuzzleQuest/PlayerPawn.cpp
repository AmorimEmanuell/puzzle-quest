// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CellChecker.h"
#include "SaveData.h"
#include "Health.h"
#include "PuzzleQuestPlayerState.h"

APlayerPawn::APlayerPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainInputMappingContext, 0);
		}
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	TimeAfterLastAction += DeltaTime;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &APlayerPawn::ProcessMoveUp);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerPawn::ProcessMoveRight);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerPawn::Attack(UHealth* OtherHealth)
{
	APuzzleQuestPlayerState* MyPlayerState = Cast<APuzzleQuestPlayerState>(GetPlayerState());
	if (MyPlayerState->ConsumeStamina())
	{
		OtherHealth->TakeDamage(MyPlayerState->GetAttackPower());
		TimeAfterLastAction = 0;
	}
}

void APlayerPawn::ProcessMoveUp(const FInputActionValue& Value)
{
	if (!CanAct())
	{
		return;
	}

	float MoveDirection = Value.Get<float>();
	FVector CameraForward = Camera->GetForwardVector();
	FVector CheckDirection = GetCheckDirection(CameraForward, MoveDirection);
	ProcessNextAction(CheckCellOnDirection(CheckDirection), CheckDirection);
}

void APlayerPawn::ProcessMoveRight(const FInputActionValue& Value)
{
	if (!CanAct())
	{
		return;
	}

	float MoveDirection = Value.Get<float>();
	FVector CameraRight = Camera->GetRightVector();
	FVector CheckDirection = GetCheckDirection(CameraRight, MoveDirection);
	ProcessNextAction(CheckCellOnDirection(CheckDirection), CheckDirection);
}

void APlayerPawn::ProcessNextAction(AActor* HitActor, FVector Direction)
{
	if (HitActor == nullptr)
	{
		MoveIn(Direction);
		RotateTo(Direction);
	}
	else
	{
		if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
		{
			Interactable->OnInteract(this);
		}
	}
}
