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

	// AI�� ��ġ (�ʱ�ȭ)
	UPROPERTY(EditAnywhere, Category = "Planet Location Params")
	FVector AIPlanetLocation = FVector(3700.0f, 25280.0f, 3580.0f);

	virtual void PawnKilled(APawn* PawnKilled) override;

	// ���� �θ�Ŭ�������� ������� �����丵 �� ��!!
	virtual void PlanetKilled() override;


	void EndGame(bool bIsPlayerWinner);

	// �༺ ���� �Լ� �߰�
	void SpawnPlayerPlanet();

	void SpawnAIPlanet();

	// �༺ Ŭ���� Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "Planet")
	TSubclassOf<APlanet> PlayerPlanetClass;  // Player �༺ ������ Ŭ���� ����
	
	// �༺ Ŭ���� Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "Planet")
	TSubclassOf<APlanet> AIPlanetClass;  // AI �༺ ������ Ŭ���� ����

	APlanet* PlayerPlanet;

	APlanet* AIPlanet;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

protected:
	virtual void BeginPlay() override;

};
