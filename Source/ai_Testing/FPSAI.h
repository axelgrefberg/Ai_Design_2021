// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSAI.generated.h"

UCLASS()
class AI_TESTING_API AFPSAI : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFPSAI();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
