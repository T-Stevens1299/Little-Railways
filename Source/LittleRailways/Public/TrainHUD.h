// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrainHUD.generated.h"

/**
 * 
 */
UCLASS()
class LITTLERAILWAYS_API UTrainHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UTrainHUD(const FObjectInitializer& ObjectInitializer);
};
