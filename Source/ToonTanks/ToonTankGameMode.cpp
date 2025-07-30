// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"


void AToonTankGameMode::ActorDied(AActor *DeadActor){
    TowerDeathCount = GetTowerDeathCount();
    if(DeadActor == Tank){
        Tank->HandleDestruction();
        if(PlayerController){
          PlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)){
        DestroyedTower->HandleDestruction();
        TowerDeathCount--;
        if(TowerDeathCount == 0){
            GameOver(true);
        }
    }

}

void AToonTankGameMode::BeginPlay(){
    Super::BeginPlay();
    HandleGameStart();
    HealthUI(isHit);
}

void AToonTankGameMode::HandleGameStart(){
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    
    StartGame();

    if(PlayerController){
        PlayerController->SetPlayerEnabledState(false);


        FTimerHandle PlayerEnableTimer; 
        FTimerDelegate PlayerEnableTimerDelegate = 
        FTimerDelegate::CreateUObject(PlayerController, 
            &AToonTankPlayerController::SetPlayerEnabledState, true);
        
        GetWorldTimerManager().SetTimer(PlayerEnableTimer,
        PlayerEnableTimerDelegate, StartDelay, false);

    }
}

int32 AToonTankGameMode::GetTowerDeathCount(){
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();

}
