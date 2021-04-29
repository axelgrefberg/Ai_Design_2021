// Fill out your copyright notice in the Description page of Project Settings.


#include "FGHearingSenseComponent.h"
#include "FGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "FGCharacter.h"
#include "FGEnemy.h"


// Sets default values for this component's properties
UFGHearingSenseComponent::UFGHearingSenseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFGHearingSenseComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->HearingComponents.Add(this);
	// ...
	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), HearingDistance, 12, FColor(181, 0, 0), true, 20, 0, 2);

}

void UFGHearingSenseComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->HearingComponents.Remove(this);
}

// Called every frame
void UFGHearingSenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFGHearingSenseComponent::HeardNoise(float NoiseRadius, AFGCharacter* NoiseOriginCharacter)
{
	float DistanceToNoise = FVector::Dist(NoiseOriginCharacter->GetActorLocation(), GetOwner()->GetActorLocation());
	if (FMath::Square(DistanceToNoise) < (FMath::Square(NoiseRadius) + FMath::Square(HearingDistance)))
	{
		
		Cast<AFGEnemy>(GetOwner())->CurrentTarget = NoiseOriginCharacter->GetActorLocation();
		DrawDebugSphere(GetWorld(), NoiseOriginCharacter->GetActorLocation(), NoiseRadius, 12, FColor(181, 0, 0), true, 2, 0, 2);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("We HEar YoU"));
		NoiseOriginCharacter->Timer = 0;
	}
}


