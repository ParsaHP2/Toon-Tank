// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if (InFireRange()){
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction(){
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay(){

    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandler, 
        this, 
        &ATower::CheckFireCondition, 
        FireRate, 
        true);
}

void ATower::CheckFireCondition(){
    if(Tank == nullptr) return;
    
    if(InFireRange() && Tank->bAlive){
        Fire();
    }

}

bool ATower::InFireRange(){
    if (Tank){
        float distance = FVector::Dist(GetActorLocation(), 
        Tank->GetActorLocation());

        if(distance <= FireRange){
            return true;
        }
    }
    return false;
}
