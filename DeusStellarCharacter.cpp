// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeusStellarCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Atom.h"
#include "Components/CapsuleComponent.h"
#include "DeusStellar2GameMode.h"
#include "DeusStellarCameraShake.h"
#include "GameFramework/Character.h"  
#include "DeusStellarPlayerController.h"
#include <Net/UnrealNetwork.h>


//////////////////////////////////////////////////////////////////////////
// ADeusStellarCharacter

ADeusStellarCharacter::ADeusStellarCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	//// 기본 이동 모드 설정
	GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;
	GetCharacterMovement()->DefaultWaterMovementMode = MOVE_Flying;

	//// 비행 속도 조정
	GetCharacterMovement()->MaxFlySpeed = MaxFlySpeed;


	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// 기본 생성자에서 비행 이동 컴포넌트 생성
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));




	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ADeusStellarCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Planet = nullptr;

	Atom = GetWorld()->SpawnActor<AAtom>(AtomClass);
	// 아톰이 정상적으로 스폰되었는지 확인
	if (Atom)
	{
		FRotator AttachRotation = FRotator::ZeroRotator; // 기본 회전

		// 아톰을 캡슐 컴포넌트에 부착
		Atom->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);

		// 캡슐 컴포넌트를 기준으로 아톰의 상대 위치 설정
		Atom->SetActorRelativeLocation(AtomAttachLocation);
		Atom->SetActorRotation(AttachRotation); // 원하는 회전 설정
		Atom->SetOwner(this);
	}

}

// Called every frame
void ADeusStellarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//////////////////////////////////////////////////////////////////////////
// Input

void ADeusStellarCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADeusStellarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADeusStellarCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADeusStellarCharacter::Look);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ADeusStellarCharacter::Shoot);

		// Dash Start
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ADeusStellarCharacter::StartDashing);

		// Dash End
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &ADeusStellarCharacter::StopDashing);

		// Shooting
		EnhancedInputComponent->BindAction(QuitAction, ETriggerEvent::Started, this, &ADeusStellarCharacter::Quit);
		
	}

}

void ADeusStellarCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	/*FVector2D MovementVector = Value.Get<FVector2D>();*/
	FVector MovementVector = Value.Get<FVector>();


	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		const FVector UpDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Z);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y );
		AddMovementInput(RightDirection, MovementVector.X );
		AddMovementInput(UpDirection, MovementVector.Z );

	}
}

void ADeusStellarCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


void ADeusStellarCharacter::Quit(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Restarting Level"));
	if (ADeusStellarPlayerController* PC = Cast<ADeusStellarPlayerController>(GetController()))
	{
		PC->UserQuitGame();
	}
}

//void ADeusStellarCharacter::Shoot_RPC_Implementation()
//{
//	Shoot_Broadcast_RPC();
//}
//
//void ADeusStellarCharacter::Shoot_Broadcast_RPC_Implementation()
//{
//	if (GEngine)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Complete"));
//	}
//
//	Shoot();
//}

void ADeusStellarCharacter::Shoot()
{
	Atom->PullTrigger(false, FVector(0,0,0));
}

void ADeusStellarCharacter::ShootFromAI(bool bIsPlayerTarget, FVector TargetLocation)
{
	Atom->PullTrigger(bIsPlayerTarget, TargetLocation);
}


//void ADeusStellarCharacter::StartDashing_RPC_Implementation()
//{
//	StartDashing_Broadcast_RPC();
//}
//
//
//void ADeusStellarCharacter::StartDashing_Broadcast_RPC_Implementation()
//{
//
//	StartDashing();
//}


void ADeusStellarCharacter::StartDashing()
{
	if (!bIsDashing)
	{
		bIsDashing = true;
		GetCharacterMovement()->MaxFlySpeed *= DashSpeedMultiplier;

		DashEffect();
	}

}

//void ADeusStellarCharacter::StopDashing_RPC_Implementation()
//{
//	StopDashing_Broadcast_RPC();
//}
//
//
//void ADeusStellarCharacter::StopDashing_Broadcast_RPC_Implementation()
//{
//	StopDashing();
//}


void ADeusStellarCharacter::StopDashing()
{
	if (bIsDashing)
	{
		bIsDashing = false;
		GetCharacterMovement()->MaxFlySpeed /= DashSpeedMultiplier;
	}
}




float ADeusStellarCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	/*TakeDamageEffect();*/

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
	}*/

	if (IsDead())
	{
		if (Atom)
		{
			Atom->OnDeath();
		}

		ADeusStellar2GameMode* GameMode = GetWorld()->GetAuthGameMode<ADeusStellar2GameMode>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}


bool ADeusStellarCharacter::IsDead() const
{
	return Health <= 0;
}


float ADeusStellarCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}


void ADeusStellarCharacter::TakeDamageEffect()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UDeusStellarCameraShake* CameraShakeInstance = NewObject<UDeusStellarCameraShake>())
		{
			CameraShakeInstance->SetDamageShake();  // 너가 만든 함수 호출
			PC->ClientStartCameraShake(CameraShakeInstance->GetClass());
		}
	}
}


void ADeusStellarCharacter::DashEffect()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UDeusStellarCameraShake* CameraShakeInstance = NewObject<UDeusStellarCameraShake>())
		{
			CameraShakeInstance->SetDashShake();  // 너가 만든 함수 호출
			PC->ClientStartCameraShake(CameraShakeInstance->GetClass());
		}
	}
}


/////////////////////// 네트워크


void ADeusStellarCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// bIsDashing을 리플리케이션 대상으로 설정
	DOREPLIFETIME(ADeusStellarCharacter, bIsDashing);
	// Health을 리플리케이션 대상으로 설정
	DOREPLIFETIME(ADeusStellarCharacter, Health);
}
