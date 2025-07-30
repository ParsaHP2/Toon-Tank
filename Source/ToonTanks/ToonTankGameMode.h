// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

	bool isHit = false;

	UFUNCTION(BlueprintImplementableEvent)
	void HealthUI(bool TankisHit);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTankPlayerController* PlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TowerDeathCount = 0;
	int32 GetTowerDeathCount();
	
};
