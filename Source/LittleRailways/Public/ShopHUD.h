// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Blueprint/UserWidget.h"
#include "LittleRailways/LittleRailwaysGameMode.h"
#include "ShopHUD.generated.h"

class ASpawningTrack;

USTRUCT(BlueprintType)
struct FShopData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AssetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int requiredLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int requiredFunds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText buildDate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText wheelArrangement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText tractiveEffort;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText HistoryText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AActor> LocoVariation1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AActor> LocoVariation2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AActor> LocoVariation3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isLoco;

};

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

	void setShopScreen(int rowToFind);

	UFUNCTION()
	void nextAsset();

	UFUNCTION()
	void previousAsset();

	UFUNCTION()
	void closeShopWindow();

	void setupSpawnTrackArray();

	UFUNCTION(BlueprintCallable)
	bool trackCheck(int passedIndex);

	void spawnBoughtItem(int passedIndex);

	UFUNCTION()
	void changeColourVariation();

	UFUNCTION(BlueprintCallable)
	void purchasingCheck();

	//Variables
	ALittleRailwaysGameMode* GMref;

	APlayerController* PC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle dataTableRef;

	FShopData* currentRow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int totalRows;

	int currentRowIndex = 1;

	int colourVariation = 1;

	int requiredFunds;
	int requiredLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "spawnTracks")
	TArray<ASpawningTrack*> tracksToSpawnObjects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> TrackClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> productToBuy;

	//UI Components
	//Buttons
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* NextButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PreviousButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* VariationButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BuyButton;

	//Text
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurrentFunds;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurentLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AssetName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AssetFunds;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AssetLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* History;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BuildDate;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* WheelArrangement;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TractiveEffort;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* WheelsCapacity;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TEgoodstype;
};