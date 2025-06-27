#include "BTTask_MoveToFly.h"
#include "DeusStellarCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "DeusStellarAIController.h"


UBTTask_MoveToFly::UBTTask_MoveToFly()
{
    NodeName = TEXT("Move To Fly");
}

EBTNodeResult::Type UBTTask_MoveToFly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // AIController가 유효한지 체크
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // AI의 Pawn 가져오기
    ADeusStellarCharacter* AICharacter = Cast<ADeusStellarCharacter>(AIController->GetPawn());
    if (AICharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // 목표 위치를 Blackboard에서 가져오기
    FVector TargetLocation;
    bool result = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("CanAttackPlayer"));

    // 플레이어를 따라가라
    if (result)
    {
        TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation"));
    }
    // 행성을 따라가라
    else
    {
        TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlanetLocation"));
    }

    // 비행 처리
    MoveAIToTarget(AIController, TargetLocation);

    return EBTNodeResult::Succeeded;
}


void UBTTask_MoveToFly::MoveAIToTarget(AAIController* AIController, const FVector& TargetLocation)
{
    if (AIController)
    {
        APawn* AIPawn = AIController->GetPawn();
        if (AIPawn)
        {
            // AIPawn의 CharacterMovementComponent를 가져옴
            UCharacterMovementComponent* CharacterMovement = AIPawn->FindComponentByClass<UCharacterMovementComponent>();
            if (CharacterMovement)
            {
                // DeusStellarAIController를 가져와서 속도와 제동속도를 설정
                ADeusStellarAIController* DeusAIController = Cast<ADeusStellarAIController>(AIController);
                if (DeusAIController)
                {
                    // DeusStellarAIController에서 MaxFlySpeed와 BrakingDecelerationFlying 값을 가져옴
                    float MaxFlySpeed = DeusAIController->MaxFlySpeed; // 예: 1000.0f
                    float BrakingDecelerationFlying = DeusAIController->BrakingDecelerationFlying; // 예: 500.0f

                    // 비행 모드로 설정 (Flying)
                    CharacterMovement->SetMovementMode(EMovementMode::MOVE_Flying);

                    // 비행 속도 설정
                    CharacterMovement->MaxFlySpeed = MaxFlySpeed;
                    CharacterMovement->BrakingDecelerationFlying = BrakingDecelerationFlying;
                }

                // 현재 위치와 목표 지점 간의 방향 벡터 계산
                FVector CurrentLocation = AIPawn->GetActorLocation();
                FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

                // 이동 방향에 벡터를 추가 (속도는 MaxFlySpeed와 함께 반영됨)
                CharacterMovement->Launch(FVector(Direction * CharacterMovement->MaxFlySpeed));

                // 회전 처리 (목표 지점으로 회전)
                FRotator LookAtRotation = (TargetLocation - CurrentLocation).Rotation();
                AIPawn->SetActorRotation(FMath::RInterpTo(AIPawn->GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 5.0f)); // 회전 속도 조절
            }
        }
    }
}

