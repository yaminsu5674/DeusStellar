// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "DeusStellarAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API ADeusStellarAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	APawn* PlayerPawn;
	UFloatingPawnMovement* FloatingMovement;


public:
	ADeusStellarAIController();

	UPROPERTY(EditAnywhere, Category = "AI Params")
	float RecognizeDistance = 3000;

	UPROPERTY(EditAnywhere, Category = "AI Params")
	float MaxFlySpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "AI Params")
	float BrakingDecelerationFlying = 1000.0f;

	virtual void Tick(float DeltaSeconds) override;

	bool IsDead() const;


protected:
	virtual void BeginPlay() override;

	/*void MoveAIFly(float DeltaSeconds);*/
	
};
