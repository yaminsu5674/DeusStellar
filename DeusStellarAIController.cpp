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
    // 기본 값으로 nullptr로 초기화
    PlayerPawn = nullptr;
    FloatingMovement = nullptr;
    // 비해비어 트리 블루프린트에서 초기화.
   
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

    // 아래 내용 서비스랑 중복돼서 일단 주석처리해놓음.

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
//    // 한 번만 PlayerPawn을 초기화
//    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
//    if (PlayerPawn)
//    {
//        SetFocus(PlayerPawn);
//    }
//
//    // 한 번만 UFloatingPawnMovement를 찾고 캐싱
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
//    //// AI가 조종하는 폰의 체력을 확인
//    //ADeusStellarCharacter* AICharacter = Cast<ADeusStellarCharacter>(GetPawn());
//    //if (AICharacter && AICharacter->IsDead())
//    //{
//    //    // 체력이 0 이하일 때 이동 멈추기
//    //    FloatingMovement->StopMovementImmediately();  // 즉시 이동을 멈춤
//    //    return;  // 체력이 0 이하인 경우 더 이상 이동 처리하지 않음
//    //}
//
//    MoveAIFly(DeltaSeconds);
//}
//
//
//void ADeusStellarAIController::MoveAIFly(float DeltaSeconds)
//{
//
//    //// 현재 AI와 플레이어 사이 거리 계산
//    //float DistanceToPlayer = FVector::Dist(AILocation, PlayerLocation);
//
//    //// 일정 거리(200)보다 가까우면 이동 멈춤
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
//    // AI가 플레이어를 향하도록 회전
//    FRotator LookAtRotation = (PlayerLocation - AILocation).Rotation();
//    GetPawn()->SetActorRotation(FMath::RInterpTo(GetPawn()->GetActorRotation(), LookAtRotation, DeltaSeconds, 2.0f));
//
//    // 이동 벡터 계산 후 UFloatingPawnMovement에 전달
//    FVector Direction = (PlayerLocation - AILocation).GetSafeNormal();
//    FloatingMovement->AddInputVector(Direction * MovementSpeed);
//}

