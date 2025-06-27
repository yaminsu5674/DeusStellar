// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeusStellar2GameMode.h"
#include "Planet.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API AKillEmAllGameMode : public ADeusStellar2GameMode
{
	GENERATED_BODY()

public:
	AKillEmAllGameMode();

	UPROPERTY(EditAnywhere, Category = "Planet Location Params")
	FVector PlayerPlanetLocation = FVector(3700.0f, -21340.0f, 3580.0f);

	// AI의 위치 (초기화)
	UPROPERTY(EditAnywhere, Category = "Planet Location Params")
	FVector AIPlanetLocation = FVector(3700.0f, 25280.0f, 3580.0f);

	virtual void PawnKilled(APawn* PawnKilled) override;

	// 추후 부모클래스에서 정의토록 리팩토링 할 것!!
	virtual void PlanetKilled() override;


	void EndGame(bool bIsPlayerWinner);

	// 행성 스폰 함수 추가
	void SpawnPlayerPlanet();

	void SpawnAIPlanet();

	// 행성 클래스 타입
	UPROPERTY(EditDefaultsOnly, Category = "Planet")
	TSubclassOf<APlanet> PlayerPlanetClass;  // Player 행성 스폰용 클래스 변수
	
	// 행성 클래스 타입
	UPROPERTY(EditDefaultsOnly, Category = "Planet")
	TSubclassOf<APlanet> AIPlanetClass;  // AI 행성 스폰용 클래스 변수

	APlanet* PlayerPlanet;

	APlanet* AIPlanet;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

protected:
	virtual void BeginPlay() override;

};
