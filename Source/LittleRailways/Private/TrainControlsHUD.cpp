// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainControlsHUD.h"

UTrainControlsHUD::UTrainControlsHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UTrainControlsHUD::SpeedCalculator(float speedPassed)
{
	FString speedOutput = FString::SanitizeFloat(speedPassed);
	OnSpeedChanged(FText::FromString(FString("Speed: " + speedOutput + "km/h")));
}