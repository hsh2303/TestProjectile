// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectileGameMode.h"
#include "TestProjectileCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestProjectileGameMode::ATestProjectileGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
