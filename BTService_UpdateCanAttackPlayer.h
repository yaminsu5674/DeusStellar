// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateCanAttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API UBTService_UpdateCanAttackPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateCanAttackPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	

};
