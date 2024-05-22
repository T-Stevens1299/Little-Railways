// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignalBoxControlsHUD.generated.h"

UCLASS()
class LITTLERAILWAYS_API USignalBoxControlsHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	//Functions
	USignalBoxControlsHUD(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void setPointsOnMap();

	//Variables
	TArray<bool> pointStatus;

	//References
	class ASignalBoxConsole* SBref;

	void SetPtr(ASignalBoxConsole* SBptr);

	UFUNCTION(BlueprintCallable)
	void pointClicked(int arrayIndex);

	UFUNCTION()
	void closeWindow();

	//Binded Widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;
	
};