// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Atom.generated.h"

UCLASS()
class DEUSSTELLAR2_API AAtom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAtom();

	UParticleSystemComponent* ParticleComponent = nullptr;

	void OnDeath();

	void PullTrigger(bool bIsPlayerTarget = true, FVector TargetLocation = FVector::ZeroVector);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Atom Params")
	UParticleSystem* StarCluster1;

	UPROPERTY(EditAnywhere, Category = "Atom Params")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Atom Params")
	float MaxRange = 80000;

	UPROPERTY(EditAnywhere, Category = "Atom Params")
	float Damage = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool AtomTrace(FHitResult& Hit, FVector& ShotDirection, bool bIsPlayerTarget = true, FVector TargetLocation = FVector::ZeroVector);

	AController* GetOwnerController() const;

	void CalculateAimDirection(FVector& OutStart, FVector& OutEnd, bool bIsPlayerTarget = true, FVector TargetLocation = FVector::ZeroVector) const;


};
