// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HunterBullet.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BrayanLastExamCharacter.generated.h"


UCLASS(config=Game)
class ABrayanLastExamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	ABrayanLastExamCharacter();

	UPROPERTY(EditAnywhere, Category="Bullet")
	TSubclassOf<AHunterBullet> HunterBullet;

	UPROPERTY(EditAnywhere, Category="Bullet")
	int32 LaunchForce;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,ReplicatedUsing=OnRep_Hunter)
	bool bisHunter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,ReplicatedUsing=OnRep_Prey)
	bool bisPrey;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanShoot;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UFUNCTION(Server, Reliable)
	void Server_Shoot();

	UFUNCTION(BlueprintCallable)
	void StartShoot();

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void OnRep_Hunter();

	UFUNCTION()
	void OnRep_Prey();

	UFUNCTION()
	void IsHunter();

	UFUNCTION()
	void IsPrey();

	UFUNCTION(BlueprintImplementableEvent)
	void PreyUI();

	UFUNCTION(BlueprintImplementableEvent)
	void HunterUI();

	UFUNCTION()
	void CanDie();

	UFUNCTION(BlueprintImplementableEvent)
	void Die();

	UFUNCTION(BlueprintImplementableEvent)
	void DesactiveInput();

	UFUNCTION(BlueprintImplementableEvent)
	void ActiveInput();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();

	UFUNCTION(BlueprintCallable)
	void JoinSession();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccess);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName Session, EOnJoinSessionCompleteResult::Type Result);

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};

