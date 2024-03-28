// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "TrainControlsHUD.h"
#include "LocoController.h"

UTrainControlsHUD::UTrainControlsHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UTrainControlsHUD::SpeedCalculator(float speedPassed)
{
	FString speedOutput = FString::SanitizeFloat(speedPassed);
	OnSpeedChanged(FText::FromString(FString("Speed: " + speedOutput + "km/h")));
}

void UTrainControlsHUD::SetTrainPtr(ALocoController *TrainPrt)
{
	TrainRef = TrainPrt;
}

void UTrainControlsHUD::MoveRegSlider(float passedValue)
{
	int temp = (int)passedValue;
	TrainRef->setRegStage(temp);
}

void UTrainControlsHUD::MoveRevSlider(float passedValue)
{
	int temp = (int)passedValue;
	TrainRef->setReverserStage(temp);
}

void UTrainControlsHUD::MoveBrakeSlider(float passedValue)
{
	int temp = (int)passedValue;
	TrainRef->setBrakeStage(temp);
}