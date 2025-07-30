// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankGameMode.h"
#include "Tank.h"
#include "Global.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	GameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser){
	if(Damage <= 0.f) return;

	UGlobal* Global = Cast<UGlobal>(UGameplayStatics::GetGameInstance(GetWorld()));

	//if(Global && Global->bIsPlayerHit){
		Health -= Damage;
		//Global->bIsPlayerHit = true;
		//UE_LOG(LogTemp, Warning, TEXT("Health updated!! isHit is: %s"), Global->bIsPlayerHit ? TEXT("true") : TEXT("false"));
	//}
	

	if(Health <= 0.f && GameMode){
		GameMode->ActorDied(DamagedActor);
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}