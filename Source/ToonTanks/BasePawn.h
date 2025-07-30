// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretMesh;
  

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadOnly, Category = "Components")
	USceneComponent* ProSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Variable", meta = (AllowPrivateAccess = "true"))
	int32 VisAnywhereInt = 12;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Super Variable", meta = (AllowPrivateAccess = "true"))
	int32 EdAnywhereInt = 12;

	UPROPERTY(EditDefaultsOnly, Category= "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
