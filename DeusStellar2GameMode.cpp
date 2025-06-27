// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeusStellar2GameMode.h"
#include "DeusStellar2Character.h"
#include "UObject/ConstructorHelpers.h"

ADeusStellar2GameMode::ADeusStellar2GameMode()
{
	// set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_DeusStellarCharacter"));

    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

}



void ADeusStellar2GameMode::PawnKilled(APawn* PawnKilled)
{

}

void ADeusStellar2GameMode::PlanetKilled()
{

}

