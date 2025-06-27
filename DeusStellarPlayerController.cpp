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

	// 현재 게임 모드를 확인
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	if (CurrentGameMode && CurrentGameMode->IsA(ALobbyGameMode::StaticClass()))
	{
		// LobbyGameMode일 경우 마우스 커서 보이게
		bShowMouseCursor = true;
	}
	else
	{
		// LobbyGameMode가 아닐 경우 마우스 커서 숨기기
		bShowMouseCursor = false;
	}

	// 로컬 컨트롤러인지 확인 후 UI 생성
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

	// UI 제거도 로컬 컨트롤러에서만 실행
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
			// 로비로 이동.
			UGameplayStatics::OpenLevel(world, "LobbyMap", true);
		}
	}
}
