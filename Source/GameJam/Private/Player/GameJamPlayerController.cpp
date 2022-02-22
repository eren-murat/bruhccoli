// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GameJamPlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/GameJamCharacter.h"

AGameJamPlayerController::AGameJamPlayerController() { };

void AGameJamPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);

	PlayerRef = Cast<AGameJamCharacter>(GetPawn());
}


void AGameJamPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	RotateToMouse();
}

void AGameJamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AGameJamPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGameJamPlayerController::MoveRight);
}

void AGameJamPlayerController::MoveForward(float Value)
{
	if (PlayerRef == nullptr)
	{
		PlayerRef = Cast<AGameJamCharacter>(GetPawn());
	}

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// add movement in that direction / mouse direction
	PlayerRef->AddMovementInput(Direction, Value);
}

void AGameJamPlayerController::MoveRight(float Value)
{
	if (PlayerRef == nullptr)
	{
		PlayerRef = Cast<AGameJamCharacter>(GetPawn());
	}

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction / mouse direction
	PlayerRef->AddMovementInput(Direction, Value);
}

void AGameJamPlayerController::RotateToMouse()
{
	if (PlayerRef == nullptr)
	{
		PlayerRef = Cast<AGameJamCharacter>(GetPawn());
	}
	
	const FRotator Rotation = GetDirectionToMouse();
	PlayerRef->SetActorRotation((FRotator(0.f, Rotation.Yaw, 0.f)));
}

FRotator AGameJamPlayerController::GetDirectionToMouse()
{
	if (PlayerRef == nullptr)
	{
		PlayerRef = Cast<AGameJamCharacter>(GetPawn());
	}
	
	FHitResult HitResult;

	GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		HitResult
		);

	return UKismetMathLibrary::FindLookAtRotation(PlayerRef->GetActorLocation(), HitResult.ImpactPoint);
}

