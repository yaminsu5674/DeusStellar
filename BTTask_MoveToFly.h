// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToFly.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API UBTTask_MoveToFly : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MoveToFly();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	void MoveAIToTarget(AAIController* AIController, const FVector& TargetLocation);
	
};
