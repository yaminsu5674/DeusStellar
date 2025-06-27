// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shakes/LegacyCameraShake.h"
#include "DeusStellarCameraShake.generated.h"

/**
 * 
 */
UCLASS()
class DEUSSTELLAR2_API UDeusStellarCameraShake : public ULegacyCameraShake
{
	GENERATED_BODY()

public:
	UDeusStellarCameraShake();

	// �ǰ� �� ī�޶� ��鸲 ����
	void SetDamageShake();

	// ��� �� ī�޶� ��鸲 ����
	void SetDashShake();
	
};
