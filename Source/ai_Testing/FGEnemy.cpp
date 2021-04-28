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
	//VisionSensingComponent->OnTargetSensed.AddDynamic(this, &AFGEnemy::HandleVisionSense);

}

void AFGEnemy::HandleVisionSense(const FFGVisionSensingResults& SenseInfo)
{
	/*AAIController* AIController = Cast<AAIController>(GetController());
	AIController->MoveToLocation(SenseInfo.ActorLocation);*/
}

void AFGEnemy::HandleHearingSense(const FFGVisionSensingResults& SenseInfo)
{
	
}

void AFGEnemy::Tick(float DeltaTime)
{
	FVector Direction = (CurrentTarget - GetActorLocation());
	FRotator FacingRotation = Direction.Rotation();
	FacingRotation.Roll = 0;
	FacingRotation.Pitch = 0;
	SetActorRotation(FacingRotation);
	/*FRotator Rotation = UKismetMathLibrary::MakeRotFromX(CurrentTarget);
	SetActorRotation(Rotation);*/
}
