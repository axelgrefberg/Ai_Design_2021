#pragma once

#include "AI/Sensing/FGVisionSensingComponent.h"
#include "GameFramework/Pawn.h"
#include "FGEnemy.generated.h"

class AAIController;
class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGVisionSensingComponent;
class UFGNavMovementComponent;

UCLASS()
class AFGEnemy : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category = Vision)
	UFGVisionSensingComponent* VisionSensingComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UFGNavMovementComponent* NavMovementComponent;

	UPROPERTY(BlueprintReadWrite, Category = MyCharacter)
	FVector CurrentTarget;

	AFGEnemy();

	AAIController* AIController;
	
	UFUNCTION()
	void HandleVisionSense(const FFGVisionSensingResults& SenseInfo);
	UFUNCTION()
	void HandleHearingSense(const FFGVisionSensingResults& SenseInfo);
	virtual float GetDefaultHalfHeight() const override;

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	UCapsuleComponent* GetCapsule() const { return Capsule; }
};

