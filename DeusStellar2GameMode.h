// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Planet.h"
#include "DeusStellar2GameMode.generated.h"

UCLASS(minimalapi)
class ADeusStellar2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADeusStellar2GameMode();

	virtual void PawnKilled(APawn* PawnKilled);

	virtual void PlanetKilled();

};



