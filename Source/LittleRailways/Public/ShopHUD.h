// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LittleRailways/LittleRailwaysGameMode.h"
#include "ShopHUD.generated.h"

class ASpawningTrack;
/**
 * 
 */
UCLASS()
class LITTLERAILWAYS_API UShopHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	//Functions
	UShopHUD(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetGMptr(ALittleRailwaysGameMode* GMptr);

	void updateMoneyXP();

	UFUNCTION()
	void closeShopWindow();

	void setupSpawnTrackArray();

	UFUNCTION(BlueprintCallable)
	bool spawnBoughtItem(int passedIndex);

	UFUNCTION(BlueprintCallable)
	void purchasingCheck(int requiredFunds, int requiredLevel);

	//Variables
	ALittleRailwaysGameMode* GMref;

	APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "spawnTracks")
	TArray<ASpawningTrack*> tracksToSpawnObjects;

	//UI Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurrentFunds;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurentLevel;
};