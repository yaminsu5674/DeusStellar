// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "DeusStellarAIController.h"


AKillEmAllGameMode::AKillEmAllGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_DeusStellarCharacter"));

    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // Player �༺ Ŭ���� �ʱ�ȭ
    static ConstructorHelpers::FClassFinder<APlanet> PlayerPlanetBPClass(TEXT("/Game/Blueprints/Universe/BP_PlayerPlanet"));  // Planet Blueprint ��� ����
    if (PlayerPlanetBPClass.Succeeded())
    {
        PlayerPlanetClass = PlayerPlanetBPClass.Class;  // Planet Ŭ���� �Ҵ�
    }

    // Ai �༺ Ŭ���� �ʱ�ȭ
    static ConstructorHelpers::FClassFinder<APlanet> AIPlanetBPClass(TEXT("/Game/Blueprints/Universe/BP_AIPlanet"));  // Planet Blueprint ��� ����
    if (AIPlanetBPClass.Succeeded())
    {
        AIPlanetClass = AIPlanetBPClass.Class;  // Planet Ŭ���� �Ҵ�
    }

}

void AKillEmAllGameMode::BeginPlay()
{
    Super::BeginPlay();

    // ���� ���� �� �༺ ����
    SpawnPlayerPlanet();
    SpawnAIPlanet();
}


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    // For loop over AI in World:
    for (ADeusStellarAIController* Controller : TActorRange<ADeusStellarAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);

}


void AKillEmAllGameMode::PlanetKilled()
{
    Super::PlanetKilled();
    if (PlayerPlanet && PlayerPlanet->IsDead())
    {
        EndGame(false);
    }

    if (AIPlanet && AIPlanet->IsDead())
    {
        EndGame(true);
    }

}



void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}


void AKillEmAllGameMode::SpawnPlayerPlanet()
{
    // �÷��̾� �༺ ����
    if (PlayerPlanetClass)
    {
        PlayerPlanet = GetWorld()->SpawnActor<APlanet>(PlayerPlanetClass, PlayerPlanetLocation, FRotator(0.0f, 0.0f, 0.0f));

        // �༺���� ����� �����Ǿ����� Ȯ��
        if (PlayerPlanet)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player Planet spawned at location: %s"), *PlayerPlanet->GetActorLocation().ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlanetClass is not set!"));
    }
}


void AKillEmAllGameMode::SpawnAIPlanet()
{
    // �÷��̾� �༺ ����
    if (AIPlanetClass)
    {
        AIPlanet = GetWorld()->SpawnActor<APlanet>(AIPlanetClass, AIPlanetLocation, FRotator(0.0f, 0.0f, 0.0f));

        if (AIPlanet)
        {
            UE_LOG(LogTemp, Warning, TEXT("AI Planet spawned at location: %s"), *AIPlanet->GetActorLocation().ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlanetClass is not set!"));
    }
}

float AKillEmAllGameMode::GetHealthPercent() const
{
    if (PlayerPlanet)
    {
        return PlayerPlanet->Health / PlayerPlanet->MaxHealth;
    }
    return 0;
}