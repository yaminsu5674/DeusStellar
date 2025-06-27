// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateCanAttackPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "DeusStellarCharacter.h"
#include "DeusStellarAIController.h"
#include "KillEmAllGameMode.h"

UBTService_UpdateCanAttackPlayer::UBTService_UpdateCanAttackPlayer()
{
	NodeName = TEXT("Update Value CanAttackPlayer");
}


void UBTService_UpdateCanAttackPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ADeusStellarCharacter* Character = Cast<ADeusStellarCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	ADeusStellarAIController* AIController = Cast<ADeusStellarAIController>(OwnerComp.GetAIOwner());

	if (PlayerPawn == nullptr || Character == nullptr)
	{
		return;
	}

	if (AIController == nullptr)
	{
		return;
	}

	if (OwnerComp.GetBlackboardComponent() == nullptr)
	{
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("AILocation"), Character->GetActorLocation());

	FVector AILocation = Character->GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	float DistanceToPlayer = FVector::Dist(AILocation, PlayerLocation);

	if (DistanceToPlayer < AIController->RecognizeDistance)
	{
		if (AIController->LineOfSightTo(PlayerPawn))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
	}

}