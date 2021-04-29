#include "FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/FGMovementComponent.h"
#include "FGMovementStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FGHearingSenseComponent.h"
#include "FGGameInstance.h"
#include "DrawDebugHelpers.h"
#include "FGDamageSenseComponent.h"

AFGCharacter::AFGCharacter()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 2.5f;
	BaseLookUpRate = 2.5f;

	Speed = 1000.0f;
	Gravity = 900.0f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(Capsule);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	

	MovementComponent = CreateDefaultSubobject<UFGMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(Capsule);
}

void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NoiseTimer += DeltaTime;
	DamageTimer += DeltaTime;

	FFGFrameMovement FrameMovement = MovementComponent->CreateFrameMovement();
	
	FrameMovement.AddGravity(Gravity * DeltaTime);

	if (!InputVector.IsNearlyZero())
	{
		FVector Forward = FVector::VectorPlaneProject(FirstPersonCameraComponent->GetForwardVector(), FVector::UpVector);
		FVector ForwardMovement = Forward * InputVector.X;
		FVector Right = FirstPersonCameraComponent->GetRightVector() * InputVector.Y;
		FVector Velocity = (ForwardMovement + Right).GetSafeNormal() * Speed * DeltaTime;
		FrameMovement.AddDelta(Velocity);
	}
	MovementComponent->Move(FrameMovement);
	TakingDamage();

}

void AFGCharacter::BeginPlay()
{
	Super::BeginPlay();
	HearingListeners = Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->HearingComponents;
	DamageListeners = Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->DamageTargetComponents;

}

void AFGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFGCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently

	PlayerInputComponent->BindAxis("Turn", this, &AFGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFGCharacter::LookUpAtRate);
}

void AFGCharacter::OnFire()
{

}

void AFGCharacter::MakingNoise()
{
	if (NoiseTimer > NoiseCoolDown) 
	{
		for (UFGHearingSenseComponent* Listener : HearingListeners)
		{
			Listener->HeardNoise(NoiseRadius, this);

		}
		

	}
}

void AFGCharacter::TakingDamage()
{
	if(DamageTimer > DamageCoolDown)
	{
		for(UFGDamageSenseComponent* Listener : DamageListeners)
		{
			Listener->MadeContact(this);
		}

	}
}



void AFGCharacter::MoveForward(float Value)
{
	InputVector.X = Value;
	if(Value != 0.f)
	{
		MakingNoise();
	}
}

void AFGCharacter::MoveRight(float Value)
{
	InputVector.Y = Value;
	if (Value != 0.f)
	{
		MakingNoise();
	}
}

void AFGCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate);
}

void AFGCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate);
}
