// Copyright Epic Games, Inc. All Rights Reserved.

#include "LittleRailwaysGameMode.h"
#include "LittleRailwaysCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALittleRailwaysGameMode::ALittleRailwaysGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
