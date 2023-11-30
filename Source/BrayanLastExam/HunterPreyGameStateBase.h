// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrayanLastExamCharacter.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/GameStateBase.h"
#include "HunterPreyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BRAYANLASTEXAM_API AHunterPreyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()


	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
	int32 RandomPlayer;

	UPROPERTY(EditAnywhere)
	ABrayanLastExamCharacter* Hunter;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> Targets;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABrayanLastExamCharacter*> PlayersInGame;
	
	UPROPERTY(EditAnywhere, Category="TimeToStart", ReplicatedUsing = OnRep_InitialTimer)
	int32 InitialTime;

	UPROPERTY(EditAnywhere, Category="MatchStartTimer", ReplicatedUsing = OnRep_StartMatchTimer)
	int32 StartMatchTimer;

	UPROPERTY(EditAnywhere, Category="MatchStartTimer", ReplicatedUsing = OnRep_ReturnMenu)
	int32 ReturnTimer;

	UPROPERTY(EditAnywhere)
	int32 PlayersDead;

public:
	UFUNCTION()
	void GetPlayers();

	UFUNCTION()
	void SelectHunter();

	UFUNCTION(BlueprintCallable)
	void PlayerDead();

	UFUNCTION(BlueprintImplementableEvent)
	void HunterVictory();

	UFUNCTION(BlueprintImplementableEvent)
	void InitialTimerOff();

	UFUNCTION(BlueprintImplementableEvent)
	void StartMachtTimerOn();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartMachtTimerOff();

	UFUNCTION(BlueprintImplementableEvent)
	void ReturnMenuUI();
	
	UFUNCTION()
	void TransportPlayers();

	UFUNCTION()
	void GetTargetPoints();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
private:
	void ReduceStartTimer();

	void MatchInitialTimer();

	void ReduceMatchInitialTimer();

	void ReturnMenuTimer();
	
	void ReduceReturnMenuTimer();

	UFUNCTION()
	void OnRep_InitialTimer();

	UFUNCTION()
	void OnRep_StartMatchTimer();

	UFUNCTION()
	void OnRep_ReturnMenu();
};
