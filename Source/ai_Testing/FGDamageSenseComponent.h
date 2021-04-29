// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGDamageSenseComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFGDamageSensingDelegate);

class AFGCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_TESTING_API UFGDamageSenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFGDamageSenseComponent();
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void MadeContact(AFGCharacter* ContactOrigin);

	UPROPERTY(EditDefaultsOnly)
	float ContactDistance = 100.f;
	UPROPERTY(BlueprintAssignable)
	FFGDamageSensingDelegate OnTargetDamaged;
		
};
