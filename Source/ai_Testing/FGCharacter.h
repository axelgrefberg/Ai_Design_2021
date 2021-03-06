#pragma once

#include "GameFramework/Pawn.h"
#include "FGCharacter.generated.h"

class UFGDamageSenseComponent;
class UFGHearingSenseComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGMovementComponent;

UCLASS()
class AFGCharacter : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UFGMovementComponent* MovementComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	AFGCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	float NoiseTimer;
	float NoiseCoolDown = 2.f;
	float NoiseRadius = 200.f;
	float DamageTimer;
	float DamageCoolDown = 2.f;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay();

protected:

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Gravity;

	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void OnFire();
	void MakingNoise();
	void TakingDamage();
	TArray<UFGHearingSenseComponent*> HearingListeners;
	TArray<UFGDamageSenseComponent*> DamageListeners;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	UCapsuleComponent* GetCapsule() const { return Capsule; }

};

