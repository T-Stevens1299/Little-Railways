// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "TrainControlsHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "LocoController.h"

UTrainControlsHUD::UTrainControlsHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UTrainControlsHUD::NativeConstruct()
{
	if (AddCoal)
	{
		AddCoal->OnClicked.AddDynamic(this, &UTrainControlsHUD::OnButtonClicked);
	}
}

void UTrainControlsHUD::OnButtonClicked()
{
	TrainRef->FuelFire();
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

//Movement Functions
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

//Fuel Functions
void UTrainControlsHUD::UpdateFireLevel(float updatedFirelevel)
{
	FireLevel->SetPercent(updatedFirelevel / 100.0f);
}

void UTrainControlsHUD::UpdateWaterLevel(float updatedWaterLevel)
{
	WaterLevel->SetPercent((updatedWaterLevel / totalWaterLevel));
}

void UTrainControlsHUD::UpdateCoalLevel(float updatedCoalLevel)
{
	CoalLevel->SetPercent((updatedCoalLevel / totalCoalLevel));
}