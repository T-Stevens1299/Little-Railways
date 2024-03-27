// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrainControlsHUD.generated.h"

/**
 * 
 */
UCLASS()
class LITTLERAILWAYS_API UTrainControlsHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UTrainControlsHUD(const FObjectInitializer& ObjectInitializer);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Widget")
	void OnSpeedChanged(const FText& CurrentSpeedText);

public:
	void SpeedCalculator(float speedPassed);

	class ALocoController* TrainRef;

	void SetTrainPtr(ALocoController* TrainPrt);

	UFUNCTION(BlueprintCallable, Category = "Slider")
	void MoveRegSlider(float passedValue);

	UFUNCTION(BlueprintCallable, Category = "Slider")
	void MoveRevSlider(float passedValue);

	UFUNCTION(BlueprintCallable, Category = "Slider")
	void MoveBrakeSlider(float passedValue);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* RegulatorSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* ReverserSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* BreakSlider;
};
