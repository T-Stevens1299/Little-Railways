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

	void ToggleHUD();

	int currentXP;

	int currentMoney;

	int currentLevel;

	bool HUDon = false;

	/** HUD Widget */
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> HUDref;

	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class UPlayerProgressionHUD* HUD;

	APlayerController* PC;
};