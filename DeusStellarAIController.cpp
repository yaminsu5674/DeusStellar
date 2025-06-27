// Fill out your copyright notice in the Description page of Project Settings.

#include "DeusStellarAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "DeusStellarCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KillEmAllGameMode.h"


ADeusStellarAIController::ADeusStellarAIController()
{
    // �⺻ ������ nullptr�� �ʱ�ȭ
    PlayerPawn = nullptr;
    FloatingMovement = nullptr;
    // ���غ�� Ʈ�� �������Ʈ���� �ʱ�ȭ.
   
}



void ADeusStellarAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        AKillEmAllGameMode* GameMode = Cast<AKillEmAllGameMode>(GetWorld()->GetAuthGameMode());
        
        GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttackPlayer"), false);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        if (GameMode != nullptr)
        {
            GetBlackboardComponent()->SetValueAsVector(TEXT("PlanetLocation"), GameMode->PlayerPlanetLocation);
        }
        

    }
}


void ADeusStellarAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // �Ʒ� ���� ���񽺶� �ߺ��ż� �ϴ� �ּ�ó���س���.

    /*if (LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }*/
}


bool ADeusStellarAIController::IsDead() const
{
    ADeusStellarCharacter* ControlledCharacter = Cast<ADeusStellarCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    
    return true;  
}

















//void ADeusStellarAIController::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // �� ���� PlayerPawn�� �ʱ�ȭ
//    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
//    if (PlayerPawn)
//    {
//        SetFocus(PlayerPawn);
//    }
//
//    // �� ���� UFloatingPawnMovement�� ã�� ĳ��
//    if (GetPawn())
//    {
//        FloatingMovement = GetPawn()->FindComponentByClass<UFloatingPawnMovement>();
//    }
//}
//
//
//
//
//void ADeusStellarAIController::Tick(float DeltaSeconds)
//{
//    Super::Tick(DeltaSeconds);
//
//    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
//
//    if (LineOfSightTo(PlayerPawn))
//    {
//        SetFocus(PlayerPawn);
//        MoveAIFly(DeltaSeconds);
//    }
//
//    else
//    {
//        ClearFocus(EAIFocusPriority::Gameplay);
//        StopMovement();
//    }
//
//    //// AI�� �����ϴ� ���� ü���� Ȯ��
//    //ADeusStellarCharacter* AICharacter = Cast<ADeusStellarCharacter>(GetPawn());
//    //if (AICharacter && AICharacter->IsDead())
//    //{
//    //    // ü���� 0 ������ �� �̵� ���߱�
//    //    FloatingMovement->StopMovementImmediately();  // ��� �̵��� ����
//    //    return;  // ü���� 0 ������ ��� �� �̻� �̵� ó������ ����
//    //}
//
//    MoveAIFly(DeltaSeconds);
//}
//
//
//void ADeusStellarAIController::MoveAIFly(float DeltaSeconds)
//{
//
//    //// ���� AI�� �÷��̾� ���� �Ÿ� ���
//    //float DistanceToPlayer = FVector::Dist(AILocation, PlayerLocation);
//
//    //// ���� �Ÿ�(200)���� ������ �̵� ����
//    //if (DistanceToPlayer <= 200.0f)
//    //{
//    //    FloatingMovement->StopMovementImmediately();
//    //    return;
//    //}
//
//    if (!PlayerPawn || !GetPawn() || !FloatingMovement) return;
//
//
//    FVector PlayerLocation = PlayerPawn->GetActorLocation();
//    FVector AILocation = GetPawn()->GetActorLocation();
//
//    // AI�� �÷��̾ ���ϵ��� ȸ��
//    FRotator LookAtRotation = (PlayerLocation - AILocation).Rotation();
//    GetPawn()->SetActorRotation(FMath::RInterpTo(GetPawn()->GetActorRotation(), LookAtRotation, DeltaSeconds, 2.0f));
//
//    // �̵� ���� ��� �� UFloatingPawnMovement�� ����
//    FVector Direction = (PlayerLocation - AILocation).GetSafeNormal();
//    FloatingMovement->AddInputVector(Direction * MovementSpeed);
//}

