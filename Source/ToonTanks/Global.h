// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Global.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UGlobal : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerState")
    bool bIsPlayerHit = false;
};
