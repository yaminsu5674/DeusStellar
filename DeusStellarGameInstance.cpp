// Fill out your copyright notice in the Description page of Project Settings.

#include "DeusStellarGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/WorldSettings.h"
#include "TwoPlayerGameMode.h"
#include "KillEmAllGameMode.h"

void UDeusStellarGameInstance::StartListenServer()
{
    // ���� ��带 TwoPlayerGameMode�� ����
    auto world = GEngine->GetCurrentPlayWorld();
    if (world)
    {
        AWorldSettings* WorldSettings = world->GetWorldSettings();
        if (WorldSettings)
        {
            // ���� ��带 ����
            WorldSettings->DefaultGameMode = ATwoPlayerGameMode::StaticClass();
            UGameplayStatics::OpenLevel(world, "MultiSpaceMap", true, "?listen");
        }
    }
}

void UDeusStellarGameInstance::JoinAsClient(FString IPAddress)
{
    // ���� ��带 TwoPlayerGameMode�� ����
    auto world = GEngine->GetCurrentPlayWorld();
    if (world)
    {
        AWorldSettings* WorldSettings = world->GetWorldSettings();
        if (WorldSettings)
        {
            // ���� ��带 ����
            WorldSettings->DefaultGameMode = ATwoPlayerGameMode::StaticClass();
            UGameplayStatics::OpenLevel(world, *IPAddress, true, "?join");
        }
    }
}

void UDeusStellarGameInstance::LeaveGame()
{
    // ���� ��带 �⺻ KillEmAllGameMode�� ����
    auto world = GEngine->GetCurrentPlayWorld();
    if (world)
    {
        AWorldSettings* WorldSettings = world->GetWorldSettings();
        if (WorldSettings)
        {
            // ���� ��带 ����
            WorldSettings->DefaultGameMode = AKillEmAllGameMode::StaticClass();
            UGameplayStatics::OpenLevel(world, "LobbyMap", true);
        }
    }
}

void UDeusStellarGameInstance::StartSingle()
{
    // ���� ��带 KillEmAllGameMode�� ����
    auto world = GEngine->GetCurrentPlayWorld();
    if (world)
    {
        AWorldSettings* WorldSettings = world->GetWorldSettings();
        if (WorldSettings)
        {
            // ���� ��带 ����
            WorldSettings->DefaultGameMode = AKillEmAllGameMode::StaticClass();
            UGameplayStatics::OpenLevel(world, "SpaceMap", true);
        }
    }
}

void UDeusStellarGameInstance::Init()
{
    Super::Init();

    // UWorld�� ���� GetNetMode() ȣ��
    UWorld* World = GetWorld();
    if (World)
    {
        ENetMode NetMode = World->GetNetMode();
        FString NetModeStr;

        switch (NetMode)
        {
        case NM_Standalone:
            NetModeStr = TEXT("Standalone");
            break;
        case NM_DedicatedServer:
            NetModeStr = TEXT("DedicatedServer");
            break;
        case NM_ListenServer:
            NetModeStr = TEXT("ListenServer");
            break;
        case NM_Client:
            NetModeStr = TEXT("Client");
            break;
        default:
            NetModeStr = TEXT("Unknown");
            break;
        }

        //// ������ ���� �޽��� ���
        //if (NetMode == NM_ListenServer)
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("This is Server: %s"), *NetModeStr));
        //}
        //// Ŭ���̾�Ʈ�� ���� �޽��� ���
        //else if (NetMode == NM_Client)
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("This is Client: %s"), *NetModeStr));
        //}
        //else
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("This is Client: %s"), *NetModeStr));
        //}
    }
}
