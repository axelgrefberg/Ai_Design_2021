#pragma once

#include "GameFramework/Pawn.h"
#include "FPSPlayer.generated.h"

class UCameraComponent;
class UCapsuleComponent;

UCLASS()
class AI_TESTING_API AFPSPlayer : public APawn
{
	GENERATED_BODY()



public:
	// Sets default values for this pawn's properties
	AFPSPlayer();	// Called every frame
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

private:
	UPROPERTY(EditDefaultsOnly)
	float GravityScale;
	float ForwardInput;
	float SidewaysInput;
	FVector Movement;
	void HandleVerticalMovement(float Value);
	void HandleHorizontalMovement(float Value);
	void HandleLookHorizontal(float value);
	void HandleLookVertical(float value);
};
