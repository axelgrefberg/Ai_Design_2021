#include "FGEnemy.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI/Sensing/FGVisionSensingComponent.h"
#include "AI/Movement/FGNavMovementComponent.h"

AFGEnemy::AFGEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	VisionSensingComponent = CreateDefaultSubobject<UFGVisionSensingComponent>(TEXT("VisionSensing"));
	NavMovementComponent = CreateDefaultSubobject<UFGNavMovementComponent>(TEXT("NavMovementComponent"));
}

float AFGEnemy::GetDefaultHalfHeight() const
{
	// Don't scale...
	return Capsule->GetScaledCapsuleHalfHeight();
}

void AFGEnemy::BeginPlay()
{
	Super::BeginPlay();
	VisionSensingComponent->OnTargetSensed.AddDynamic(this, &AFGEnemy::HandleVisionSense);
	VisionSensingComponent->OnTargetLost.AddDynamic(this, &AFGEnemy::HandleVisionSense);
	AIController = Cast<AAIController>(GetController());

}

void AFGEnemy::HandleVisionSense(const FFGVisionSensingResults& SenseInfo)
{
	
	CurrentTarget = SenseInfo.ActorLocation;
	AIController->MoveToLocation(SenseInfo.ActorLocation);
}

void AFGEnemy::HandleHearingSense(const FFGVisionSensingResults& SenseInfo)
{
	
}

void AFGEnemy::Tick(float DeltaTime)
{
	FVector Velocity = NavMovementComponent->RequestedVelocity;
    if(!Velocity.IsNearlyZero())
    {
    	//Rotate towards direction it is moving in
		Velocity.Z = 0.f;
		FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		SetActorRotation(Rotation);
    }

	//Rotate towards target
	//FVector Direction = (CurrentTarget - GetActorLocation());
//	FRotator FacingRotation = Direction.Rotation();
	//FacingRotation.Roll = 0;
	//FacingRotation.Pitch = 0;
	//SetActorRotation(FacingRotation);
}
