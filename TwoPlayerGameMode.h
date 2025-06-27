// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeusStellar2GameMode.h"
#include "TwoPlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API ATwoPlayerGameMode : public ADeusStellar2GameMode
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	
};
