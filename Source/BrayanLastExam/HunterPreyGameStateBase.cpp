// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPreyGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AHunterPreyGameStateBase::GetPlayers()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	InitialTime = 0;
	InitialTimerOff();
	
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<AActor*> Players;
		UGameplayStatics::GetAllActorsOfClass(World, ABrayanLastExamCharacter::StaticClass(), Players);

		for (AActor* Player : Players)
		{
			ABrayanLastExamCharacter* MyPlayer = Cast<ABrayanLastExamCharacter>(Player);
			if (MyPlayer)
			{
				PlayersInGame.Add(MyPlayer);
			}
		}
	}
	TransportPlayers();
}

void AHunterPreyGameStateBase::SelectHunter()
{
	RandomPlayer = FMath::RandRange(0, PlayersInGame.Num() - 1);
	for (int32 i = 0; i<PlayersInGame.Num(); i++)
	{
		if (i == RandomPlayer)
		{
			PlayersInGame[i]->IsHunter();
			Hunter = PlayersInGame[i];
		}
		else
		{
			PlayersInGame[i]->IsPrey();
		}
	}
	StartMachtTimerOn();
	MatchInitialTimer();
}

void AHunterPreyGameStateBase::PlayerDead()
{
	PlayersDead++;
	if (PlayersDead == PlayersInGame.Num()-1)
	{
		HunterVictory();
		ReturnMenuUI();
		ReturnMenuTimer();
	}
}

void AHunterPreyGameStateBase::TransportPlayers()
{
	for (int32 i = 0; i < PlayersInGame.Num(); i++)
	{
		PlayersInGame[i]->DesactiveInput();
		PlayersInGame[i]->SetActorTransform(Targets[i]);
	}
	SelectHunter();
}

void AHunterPreyGameStateBase::GetTargetPoints()
{
	UWorld* World = GetWorld();
	TArray<AActor*> TargetPoints;

	UGameplayStatics::GetAllActorsOfClass(World, ATargetPoint::StaticClass(), TargetPoints);

	for (AActor* TargetPoint : TargetPoints)
	{
		ATargetPoint* MyTargetPoint = Cast<ATargetPoint>(TargetPoint);
		if (MyTargetPoint)
		{
			Targets.Add(MyTargetPoint->GetTransform());
		}
	}
}

void AHunterPreyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHunterPreyGameStateBase, InitialTime);
	DOREPLIFETIME(AHunterPreyGameStateBase, StartMatchTimer);
}

void AHunterPreyGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	GetTargetPoints();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHunterPreyGameStateBase::ReduceStartTimer, 1, true);
}

void AHunterPreyGameStateBase::ReduceStartTimer()
{
	InitialTime--;
	if (InitialTime <= 0)
	{
		GetPlayers();
	}
}

void AHunterPreyGameStateBase::MatchInitialTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHunterPreyGameStateBase::ReduceMatchInitialTimer, 1 , true);
}

void AHunterPreyGameStateBase::ReduceMatchInitialTimer()
{
	StartMatchTimer--;
	if (StartMatchTimer <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		StartMachtTimerOff();
		for (int32 i = 0; i < PlayersInGame.Num(); i++)
		{
			PlayersInGame[i]->ActiveInput();
		}
	}
}

void AHunterPreyGameStateBase::ReturnMenuTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHunterPreyGameStateBase::ReduceReturnMenuTimer, 1, true);
}

void AHunterPreyGameStateBase::ReduceReturnMenuTimer()
{
	ReturnTimer--;
	if (ReturnTimer <= 0)
	{
		FString Map = TEXT("MainMenu");
		UGameplayStatics::OpenLevel(GetWorld(),FName(Map));
	}
}

void AHunterPreyGameStateBase::OnRep_InitialTimer()
{
	
}

void AHunterPreyGameStateBase::OnRep_StartMatchTimer()
{
	
}

void AHunterPreyGameStateBase::OnRep_ReturnMenu()
{
	
}
