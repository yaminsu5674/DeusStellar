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

	// 피격 시 카메라 흔들림 설정
	void SetDamageShake();

	// 대시 시 카메라 흔들림 설정
	void SetDashShake();
	
};
