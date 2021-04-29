// Fill out your copyright notice in the Description page of Project Settings.


#include "FGDamageSenseComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FGGameInstance.h"
#include "FGCharacter.h"

// Sets default values for this component's properties
UFGDamageSenseComponent::UFGDamageSenseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFGDamageSenseComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->DamageTargetComponents.Add(this);
	// ...
	
}

void UFGDamageSenseComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->DamageTargetComponents.Remove(this);
}


// Called every frame
void UFGDamageSenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFGDamageSenseComponent::MadeContact(AFGCharacter* ContactOrigin)
{
	float DistanceToContact = FVector::Dist(ContactOrigin->GetActorLocation(), GetOwner()->GetActorLocation());
	if(FMath::Square(DistanceToContact) < FMath::Square(ContactDistance))
	{
		ContactOrigin->DamageTimer = 0.f;
		OnTargetDamaged.Broadcast();
		
	}
}


