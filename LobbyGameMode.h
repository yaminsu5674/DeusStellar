// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeusStellar2GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API ALobbyGameMode : public ADeusStellar2GameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
