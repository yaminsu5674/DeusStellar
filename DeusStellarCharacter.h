// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Atom.h"
#include "Planet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "DeusStellarCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS(Blueprintable)
class ADeusStellarCharacter : public ACharacter
{
	GENERATED_BODY()

	// ���� �̵� ������Ʈ
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingMovement;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Quit Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QuitAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, Category = "DeusStellar Character Params")
	float MaxFlySpeed = 1000;

	// ��� �ӵ� ����
	UPROPERTY(EditAnywhere, Category = "DeusStellar Character Params")
	float DashSpeedMultiplier = 2.0f;

	// ������ ��� ��ġ
	UPROPERTY(EditAnywhere, Category = "Atom")
	FVector AtomAttachLocation = FVector(0.0f, 0.0f, 100.0f);  // 100��ŭ Z�� �������� ������

	// ��ü�� �ƴ� Ŭ�������� �����ϴ� �뵵.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAtom> AtomClass;

	// ���� ���� ��ü�� �����ϱ� ���� �뵵.
	UPROPERTY()
	AAtom* Atom;

	// ��ü�� �ƴ� Ŭ�������� �����ϴ� �뵵.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlanet> PlanetClass;

	// ���� ���� ��ü�� �����ϱ� ���� �뵵.
	UPROPERTY()
	APlanet* Planet;

	UPROPERTY(EditAnywhere, Category = "DeusStellar Character Params")
	float MaxHealth = 100;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Health;


public:
	ADeusStellarCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimePrpos) const override;


protected:

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Dash")
	bool bIsDashing = false;


	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Quit(const FInputActionValue& Value);

	// ��� ���� �Լ�
	/*UFUNCTION(NetMulticast, Reliable)
	void StartDashing_Broadcast_RPC();

	UFUNCTION(NetMulticast, Reliable)
	void StopDashing_Broadcast_RPC();

	UFUNCTION(Server, Reliable)
	void StartDashing_RPC();

	UFUNCTION(Server, Reliable)
	void StopDashing_RPC();*/

	void StartDashing();

	void StopDashing();

	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamageEffect();

	void DashEffect();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// ���� ���� �Լ�

	/** Called for looking input */

	/*UFUNCTION(NetMulticast, Reliable)
	void Shoot_Broadcast_RPC();

	UFUNCTION(Server, Reliable)
	void Shoot_RPC();*/

	void Shoot();

	void ShootFromAI(bool bIsPlayerTarget = true, FVector TargetLocation = FVector::ZeroVector);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
