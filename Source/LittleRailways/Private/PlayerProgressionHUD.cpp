// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProgressionHUD.h"
#include "LittleRailways/LittleRailwaysGameMode.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UPlayerProgressionHUD::UPlayerProgressionHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UPlayerProgressionHUD::changeMoneyAmount(int passedMoney)
{
	FString money = FString::FromInt(passedMoney);
	MoneyAmount->SetText(FText::FromString(FString("£" + money)));
}

void UPlayerProgressionHUD::changeXPAmount(int passedXP)
{
	FString xp = FString::FromInt(passedXP);
	XPamount->SetText(FText::FromString(FString(xp)));
}

void UPlayerProgressionHUD::changeLevel(int passedLevel)
{
	FString level = FString::FromInt(passedLevel);
	CurrentLevel->SetText(FText::FromString(FString(level)));
}

void UPlayerProgressionHUD::updateProgressBar(float passedPercentage)
{
	LevelProgress->SetPercent(passedPercentage);
}