// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "DeusStellarCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");


}


EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	ADeusStellarCharacter* AICharacter = Cast<ADeusStellarCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (AICharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

    bool bIsPlayerTarget = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("CanAttackPlayer"));

    FVector TargetLocation;

    if (bIsPlayerTarget)
    {
        TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation"));
    }
    else
    {
        TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlanetLocation"));
    }

    AICharacter->ShootFromAI(bIsPlayerTarget, TargetLocation);

    return EBTNodeResult::Succeeded;
}