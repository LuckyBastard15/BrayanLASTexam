// Fill out your copyright notice in the Description page of Project Settings.


#include "InititalTimerWidget.h"

#include "HunterPreyGameStateBase.h"

void UInititalTimerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld() != nullptr)
	{
		AHunterPreyGameStateBase* HunterPreyGameStateBase = Cast<AHunterPreyGameStateBase>(GetWorld()->GetGameState());
		if (HunterPreyGameStateBase)
		{
			TimerValue = HunterPreyGameStateBase->InitialTime;
		}
	}
}
