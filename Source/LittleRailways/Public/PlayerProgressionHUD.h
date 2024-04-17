// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerProgressionHUD.generated.h"

/**
 * 
 */
UCLASS()
class LITTLERAILWAYS_API UPlayerProgressionHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPlayerProgressionHUD(const FObjectInitializer& ObjectInitializer);

	void changeMoneyAmount(int passedMoney);
	
	void changeXPAmount(int passedXP);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MoneyAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* XPamount;
};
