// Copyright Epic Games, Inc. All Rights Reserved.

#include "LittleRailwaysGameMode.h"
#include "LittleRailwaysCharacter.h"
#include "Blueprint/UserWidget.h"
#include "PlayerProgressionHUD.h"
#include <Kismet/GameplayStatics.h>
#include "UObject/ConstructorHelpers.h"

ALittleRailwaysGameMode::ALittleRailwaysGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ALittleRailwaysGameMode::BeginPlay()
{
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	HUD = CreateWidget<UPlayerProgressionHUD>(PC, HUDref);
	HUD->changeLevel(currentLevel);
	calculatePercentage();
}

void ALittleRailwaysGameMode::addXP_Implementation(int passedXP)
{
	currentXP = currentXP + passedXP;
	HUD->changeXPAmount(currentXP);
	checkLevelUp();
	calculatePercentage();
}

void ALittleRailwaysGameMode::addMoney_Implementation(int passedMoney)
{
	currentMoney = currentMoney + passedMoney;
	HUD->changeMoneyAmount(currentMoney);
}

void ALittleRailwaysGameMode::checkLevelUp()
{
	for (int i = 0; i < levelCaps.Num(); i++)
	{
		if (currentXP >= levelCaps[i])
		{
			currentLevel = i+1;
			HUD->changeLevel(currentLevel);
		}
	}
}

void ALittleRailwaysGameMode::calculatePercentage()
{
	if (currentLevel != 5)
	{
		//convert to floats - dividing from ints does not work
		float xp = currentXP - levelCaps[currentLevel - 1];
		float xpbound = levelCaps[currentLevel] - levelCaps[currentLevel - 1];

		float percentage = (xp / xpbound);

		HUD->updateProgressBar(percentage);
	}
	else
	{
		HUD->updateProgressBar(1.0f);
	}
}

void ALittleRailwaysGameMode::ToggleHUD()
{
	if (HUDon)
	{
		HUD->RemoveFromViewport();
		HUDon = false;
	}
	else
	{
		HUD->AddToViewport();
		HUDon = true;
	}
}