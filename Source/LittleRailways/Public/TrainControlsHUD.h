// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

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

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void loadPassengersTrigger();

	UFUNCTION()
	void unloadPassengersTrigger();

	virtual void NativeConstruct() override;

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

	void UpdateFireLevel(float updatedFirelevel);

	void UpdateWaterLevel(float updatedWaterLevel);

	void UpdateCoalLevel(float updatedCoalLevel);

	void ToggleButtons();

protected:

	//UI Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* RegulatorSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* ReverserSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* BreakSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* AddCoal;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* UnloadPassengers;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* LoadPassengers;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* FireLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* WaterLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* CoalLevel;

public:
	//Stored Totals
	float totalCoalLevel;
	float totalWaterLevel;

	UPROPERTY(BlueprintReadWrite)
	float percentage;

};
