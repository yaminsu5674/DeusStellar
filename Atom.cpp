// Fill out your copyright notice in the Description page of Project Settings.

#include "Atom.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
AAtom::AAtom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AAtom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAtom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAtom::PullTrigger(bool bIsPlayerTarget, FVector TargetLocation)
{
	ParticleComponent = UGameplayStatics::SpawnEmitterAttached(StarCluster1, Mesh, TEXT("StarCluster1"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = AtomTrace(Hit, ShotDirection, bIsPlayerTarget, TargetLocation);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			/*if (GetNetMode() == ENetMode::NM_ListenServer && HasAuthority())
			{
				AController* OwnerController = GetOwnerController();
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}*/
		}
	}

}


bool AAtom::AtomTrace(FHitResult& Hit, FVector& ShotDirection, bool bIsPlayerTarget, FVector TargetLocation)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return false;

	FVector Start, End;
	CalculateAimDirection(Start, End, bIsPlayerTarget, TargetLocation); // 조준 방향 계산

	ShotDirection = (End - Start).GetSafeNormal();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}


AController* AAtom::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) 
		return nullptr;
	return OwnerPawn->GetController();
}



void AAtom::CalculateAimDirection(FVector& OutStart, FVector& OutEnd, bool bIsPlayerTarget, FVector TargetLocation) const
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	OutStart = OwnerPawn->GetActorLocation();
	FRotator Rotation;

	if (OwnerController->IsPlayerController())
	{
		// 플레이어의 조준 방향
		OwnerController->GetPlayerViewPoint(OutStart, Rotation);
	}
	else
	{
		if (bIsPlayerTarget)
		{
			// AI: 가장 가까운 플레이어를 향해 조준
			if (AActor* Target = GetWorld()->GetFirstPlayerController()->GetPawn())
			{
				Rotation = (Target->GetActorLocation() - OutStart).Rotation();
			}
			else
			{
				return; // 목표 없으면 조준 안 함
			}
		}
		else
		{
			Rotation = (TargetLocation - OutStart).Rotation();
		}



	}

	OutEnd = OutStart + Rotation.Vector() * MaxRange;
}


void AAtom::OnDeath()
{
	Destroy();
}
