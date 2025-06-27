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

    // ��ü������ ��鸲�� ���̱� ���� Amplitude �� ����
    LocOscillation.Z.Amplitude = 1.0f;  // ���� 10 �� 6
    LocOscillation.Z.Frequency = 20.0f;  // ���� 25 �� 20 (���� �� �ε巴��)

    RotOscillation.Pitch.Amplitude = 1.0f;  // ���� 5 �� 3
    RotOscillation.Pitch.Frequency = 15.0f;  // ���� 20 �� 15

    RotOscillation.Yaw.Amplitude = 1.0f;  // ���� 5 �� 3
    RotOscillation.Yaw.Frequency = 15.0f;  // ���� 20 �� 15
}

void UDeusStellarCameraShake::SetDashShake()
{
    OscillationDuration = 0.2f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    // ��� �� �¿� ��鸲 ����, ���Ʒ�(Z) ��鸲�� �����ϸ鼭 ����
    LocOscillation.X.Amplitude = 0.0f;  // ���� 8 �� 0 (�¿� ��鸲 ����)
    LocOscillation.X.Frequency = 0.0f;

    LocOscillation.Z.Amplitude = 3.0f;  // ���� 5 �� 3 (���Ʒ� ��鸲 ����)
    LocOscillation.Z.Frequency = 20.0f;  // ���� 25 �� 20 (���� �� �ε巴��)

    RotOscillation.Pitch.Amplitude = 2.0f;  // ���� 3 �� 2 (�Ӹ� ȸ�� ����)
    RotOscillation.Pitch.Frequency = 10.0f;  // ���� 15 �� 10
}
