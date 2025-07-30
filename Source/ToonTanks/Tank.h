// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool isParrying = false;

	bool BuffedProjectile = false;

	float BoostedDamage = 75.f;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const {
		return TankPlayerController;
	}

	bool bAlive = true;

	int32 ParryCounter = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float Value);

	//Parry stuff
	void Parry();

	UPROPERTY(EditAnywhere, Category = "Parry")
	UMaterialInterface* ParryMaterial;

	UPROPERTY(EditAnywhere, Category = "Parry")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Dash")
	float ParryDuration = 1.f;

	float ParryTimer = 0.f;

	float LastParryTime = -100.f;
	UPROPERTY(EditAnywhere, Category = "Dash")
	float ParryCooldown = 2.0f; // 1 second cooldown
	
	//Dash stuff
	void Dash();
	bool isDashing = false;

	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashSpeed = 1500.f;

	UPROPERTY(EditAnywhere, Category = "Dash")
	float NormalSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashDuration = 0.3f;

	float DashTimer = 0.f;

	float LastDashTime = -100.f;
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashCooldown = 1.0f; // 1 second cooldown



	UPROPERTY(EditAnywhere, Category = "Movement")
	float TankSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.f;

	APlayerController* TankPlayerController;
};
