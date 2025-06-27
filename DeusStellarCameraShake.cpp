// Fill out your copyright notice in the Description page of Project Settings.

#include "DeusStellarCameraShake.h"

UDeusStellarCameraShake::UDeusStellarCameraShake()
{
    SetDamageShake();
}

void UDeusStellarCameraShake::SetDamageShake()
{
    OscillationDuration = 0.3f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    // 전체적으로 흔들림을 줄이기 위해 Amplitude 값 감소
    LocOscillation.Z.Amplitude = 1.0f;  // 기존 10 → 6
    LocOscillation.Z.Frequency = 20.0f;  // 기존 25 → 20 (조금 더 부드럽게)

    RotOscillation.Pitch.Amplitude = 1.0f;  // 기존 5 → 3
    RotOscillation.Pitch.Frequency = 15.0f;  // 기존 20 → 15

    RotOscillation.Yaw.Amplitude = 1.0f;  // 기존 5 → 3
    RotOscillation.Yaw.Frequency = 15.0f;  // 기존 20 → 15
}

void UDeusStellarCameraShake::SetDashShake()
{
    OscillationDuration = 0.2f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    // 대시 시 좌우 흔들림 제거, 위아래(Z) 흔들림만 유지하면서 줄임
    LocOscillation.X.Amplitude = 0.0f;  // 기존 8 → 0 (좌우 흔들림 제거)
    LocOscillation.X.Frequency = 0.0f;

    LocOscillation.Z.Amplitude = 3.0f;  // 기존 5 → 3 (위아래 흔들림 줄임)
    LocOscillation.Z.Frequency = 20.0f;  // 기존 25 → 20 (조금 더 부드럽게)

    RotOscillation.Pitch.Amplitude = 2.0f;  // 기존 3 → 2 (머리 회전 줄임)
    RotOscillation.Pitch.Frequency = 10.0f;  // 기존 15 → 10
}
