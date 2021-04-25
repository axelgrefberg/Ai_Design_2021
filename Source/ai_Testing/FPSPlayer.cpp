#include "FPSPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
// Sets default values
AFPSPlayer::AFPSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Camera->SetupAttachment(Capsule);
	RootComponent = Capsule;
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentInput = GetActorForwardVector() * ForwardInput + GetActorRightVector() * SidewaysInput;
	//FVector Gravity = FVector::UpVector * -GravityScale;

	AddActorWorldOffset(CurrentInput );
}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPSPlayer::HandleVerticalMovement);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFPSPlayer::HandleHorizontalMovement);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFPSPlayer::HandleLookHorizontal);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPSPlayer::HandleLookVertical);
}

void AFPSPlayer::HandleVerticalMovement(float Value)
{
	ForwardInput = Value;
}

void AFPSPlayer::HandleHorizontalMovement(float Value)
{
	SidewaysInput = Value;
}

void AFPSPlayer::HandleLookVertical(float Value)
{
	AddControllerPitchInput(Value);
}

void AFPSPlayer::HandleLookHorizontal(float Value)
{
	AddControllerYawInput(Value);

}

