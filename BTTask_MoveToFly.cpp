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

    // AIController�� ��ȿ���� üũ
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // AI�� Pawn ��������
    ADeusStellarCharacter* AICharacter = Cast<ADeusStellarCharacter>(AIController->GetPawn());
    if (AICharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // ��ǥ ��ġ�� Blackboard���� ��������
    FVector TargetLocation;
    bool result = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("CanAttackPlayer"));

    // �÷��̾ ���󰡶�
    if (result)
    {
        TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation"));
    }
    // �༺�� ���󰡶�
    else
    {
        TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlanetLocation"));
    }

    // ���� ó��
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
            // AIPawn�� CharacterMovementComponent�� ������
            UCharacterMovementComponent* CharacterMovement = AIPawn->FindComponentByClass<UCharacterMovementComponent>();
            if (CharacterMovement)
            {
                // DeusStellarAIController�� �����ͼ� �ӵ��� �����ӵ��� ����
                ADeusStellarAIController* DeusAIController = Cast<ADeusStellarAIController>(AIController);
                if (DeusAIController)
                {
                    // DeusStellarAIController���� MaxFlySpeed�� BrakingDecelerationFlying ���� ������
                    float MaxFlySpeed = DeusAIController->MaxFlySpeed; // ��: 1000.0f
                    float BrakingDecelerationFlying = DeusAIController->BrakingDecelerationFlying; // ��: 500.0f

                    // ���� ���� ���� (Flying)
                    CharacterMovement->SetMovementMode(EMovementMode::MOVE_Flying);

                    // ���� �ӵ� ����
                    CharacterMovement->MaxFlySpeed = MaxFlySpeed;
                    CharacterMovement->BrakingDecelerationFlying = BrakingDecelerationFlying;
                }

                // ���� ��ġ�� ��ǥ ���� ���� ���� ���� ���
                FVector CurrentLocation = AIPawn->GetActorLocation();
                FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

                // �̵� ���⿡ ���͸� �߰� (�ӵ��� MaxFlySpeed�� �Բ� �ݿ���)
                CharacterMovement->Launch(FVector(Direction * CharacterMovement->MaxFlySpeed));

                // ȸ�� ó�� (��ǥ �������� ȸ��)
                FRotator LookAtRotation = (TargetLocation - CurrentLocation).Rotation();
                AIPawn->SetActorRotation(FMath::RInterpTo(AIPawn->GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 5.0f)); // ȸ�� �ӵ� ����
            }
        }
    }
}

