// Fill out your copyright notice in the Description page of Project Settings.

#include "DeusStellarPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"  
#include "LobbyGameMode.h"    
#include "Kismet/GameplayStatics.h"


void ADeusStellarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ���� ���� ��带 Ȯ��
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	if (CurrentGameMode && CurrentGameMode->IsA(ALobbyGameMode::StaticClass()))
	{
		// LobbyGameMode�� ��� ���콺 Ŀ�� ���̰�
		bShowMouseCursor = true;
	}
	else
	{
		// LobbyGameMode�� �ƴ� ��� ���콺 Ŀ�� �����
		bShowMouseCursor = false;
	}

	// ���� ��Ʈ�ѷ����� Ȯ�� �� UI ����
	if (IsLocalController())
	{
		HUD = CreateWidget(this, HUDClass);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
		}
	}
}

void ADeusStellarPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// UI ���ŵ� ���� ��Ʈ�ѷ������� ����
	if (IsLocalController() && HUD != nullptr)
	{
		HUD->RemoveFromViewport();
	}

	if (IsLocalController())
	{
		if (bIsWinner)
		{
			UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
			if (WinScreen != nullptr)
			{
				WinScreen->AddToViewport();
			}
		}
		else
		{
			UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
			if (LoseScreen != nullptr)
			{
				LoseScreen->AddToViewport();
			}
		}
	}
	/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Restarting Level"));*/
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void ADeusStellarPlayerController::UserQuitGame()
{
	auto world = GEngine->GetCurrentPlayWorld();
	if (world)
	{
		AWorldSettings* WorldSettings = world->GetWorldSettings();
		if (WorldSettings)
		{
			// �κ�� �̵�.
			UGameplayStatics::OpenLevel(world, "LobbyMap", true);
		}
	}
}
