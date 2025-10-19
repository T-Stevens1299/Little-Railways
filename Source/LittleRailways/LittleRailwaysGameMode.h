// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BPI_StatsIncrease.h"
#include "GameFramework/GameModeBase.h"
#include "LittleRailwaysGameMode.generated.h"

UCLASS(minimalapi)
class ALittleRailwaysGameMode : public AGameModeBase, public IBPI_StatsIncrease
{
	GENERATED_BODY()

public:
	ALittleRailwaysGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IncreaseStatsRef")
	void addXP(int passedXP); void addXP_Implementation(int passedXP) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IncreaseStatsRef")
	void addMoney(int passedMoney); void addMoney_Implementation(int passedMoney) override;

	void checkLevelUp();

	void calculatePercentage();

	void ToggleHUD();
	
	int GetCurMoney() { return currentMoney; }

	int GetCurLevel() { return currentLevel; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProgressionData")
	int currentXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProgressionData")
	int currentMoney = 2500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProgressionData")
	int currentLevel = 1;

	bool HUDon = false;

	UPROPERTY(EditDefaultsOnly, Category = "LevelCaps")
	TArray<int> levelCaps;

	/** HUD Widget */
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> HUDref;

	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class UPlayerProgressionHUD* HUD;

	APlayerController* PC;
};