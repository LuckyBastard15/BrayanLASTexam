// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrayanLastExamGameMode.h"
#include "BrayanLastExamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABrayanLastExamGameMode::ABrayanLastExamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
