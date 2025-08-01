// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProtectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UProjectileMovementComponent* ProjectileMove;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* SmokeTrail;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, 
		AActor* otherActor,
		 UPrimitiveComponent* otherComp, 
		 FVector NormalImpulse, 
		const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	bool isImmune = false;

	int32 ParryCounter;

	float BoostedDamage = Damage + 25.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticle;

	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
