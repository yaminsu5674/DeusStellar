// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DeusStellarGameInstance.generated.h"

/**
 *
 */
UCLASS()
class DEUSSTELLAR2_API UDeusStellarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void StartSingle();
	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void StartListenServer();
	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void JoinAsClient(FString IPAddress);
	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void LeaveGame();

	virtual void Init() override;


};
