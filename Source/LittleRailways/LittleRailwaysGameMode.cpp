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
	//HUD->setGMptr(this);
}

void ALittleRailwaysGameMode::addXP_Implementation(int passedXP)
{
	currentXP = currentXP + passedXP;
	HUD->changeXPAmount(currentXP);
	checkLevelUp();
}

void ALittleRailwaysGameMode::addMoney_Implementation(int passedMoney)
{
	currentMoney = currentMoney + passedMoney;
	HUD->changeMoneyAmount(currentMoney);
}

void ALittleRailwaysGameMode::checkLevelUp()
{

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