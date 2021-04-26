// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSZombie.generated.h"

UCLASS()
class AI_TESTING_API AFPSZombie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSZombie();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
