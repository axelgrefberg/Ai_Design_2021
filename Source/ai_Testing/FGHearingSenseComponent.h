// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGHearingSenseComponent.generated.h"


class AFGCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class  UFGHearingSenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFGHearingSenseComponent();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void HeardNoise(float NoiseRadius, AFGCharacter* NoiseOriginCharacter);

	UPROPERTY(EditDefaultsOnly)
	float HearingDistance = 200.f;

		
};
