// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameJamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AGameJamPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGameJamPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	virtual void PlayerTick(float DeltaTime) override;
	
	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void RotateToMouse();

	FRotator GetDirectionToMouse();

private:
	APawn* PlayerRef;
};
