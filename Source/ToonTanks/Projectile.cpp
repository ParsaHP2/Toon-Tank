// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "Particles/ParticleSystemComponent.h"
#include "ToonTankGameMode.h"
#include "Global.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProtectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProtectileMesh;

	ProjectileMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Move"));
	ProjectileMove->InitialSpeed = 1000.f;
	ProjectileMove->MaxSpeed = 1000.f;

	SmokeTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrail->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProtectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit){
	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr) {
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();


	ATank* TankRef = Cast<ATank>(otherActor);
    UGlobal* Global = Cast<UGlobal>(GetGameInstance());
	if (TankRef && Global && TankRef->isParrying) {
		TankRef->ParryCounter++;
	    isImmune = true;  
		Global->bIsPlayerHit = false;
		UE_LOG(LogTemp, Warning, TEXT("PARRIED!! isHit is: %s"), Global->bIsPlayerHit ? TEXT("true") : TEXT("false"));
    } else if (TankRef && !TankRef->isParrying && Global){
		Global->bIsPlayerHit = true;
		UE_LOG(LogTemp, Warning, TEXT("NOT PARRIED!! isHit is: %s"), Global->bIsPlayerHit ? TEXT("true") : TEXT("false"));
	} 
	

	if (otherActor && otherActor != this && otherActor != MyOwner && !isImmune){
		
		UGameplayStatics::ApplyDamage(otherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
	    if(HitParticle)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
	 
	    if(HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

		if(HitCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	} 
	Destroy();
}
