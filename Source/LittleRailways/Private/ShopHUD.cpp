// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "ShopHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "GameManager.h"
#include "SpawningTrack.h"

UShopHUD::UShopHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UShopHUD::NativeConstruct()
{
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UShopHUD::closeShopWindow);
	}

	if (NextButton)
	{
		NextButton->OnClicked.AddDynamic(this, &UShopHUD::nextAsset);
	}

	if (PreviousButton)
	{
		PreviousButton->OnClicked.AddDynamic(this, &UShopHUD::previousAsset);
	}
}

void UShopHUD::SetGMptr(ALittleRailwaysGameMode* GMptr)
{
	GMref = GMptr;
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//setupSpawnTrackArray();
	setShopScreen(currentRowIndex);
}

void UShopHUD::updateMoneyXP()
{
	CurrentFunds->SetText(FText::FromString(FString::FromInt(GMref->GetCurMoney())));
	CurentLevel->SetText(FText::FromString(FString::FromInt(GMref->GetCurLevel())));
}

void UShopHUD::closeShopWindow()
{
	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());
	this->RemoveFromViewport();
}

void UShopHUD::setShopScreen(int rowToFind)
{
	FName rowName = FName(*(FString::FromInt(rowToFind)));
	currentRow = dataTableRef.DataTable->FindRow<FShopData>(rowName, "");

	AssetName->SetText(currentRow->AssetName);
	AssetFunds->SetText(FText::FromString(FString::FromInt(currentRow->requiredFunds)));
	AssetLevel->SetText(FText::FromString(FString::FromInt(currentRow->requiredLevel)));
	BuildDate->SetText(currentRow->buildDate);
	WheelArrangement->SetText(currentRow->wheelArrangement);
	TractiveEffort->SetText(currentRow->tractiveEffort);

	UE_LOG(LogTemp, Warning, TEXT("RowChanged"));
}

void UShopHUD::nextAsset()
{
	if ((currentRowIndex + 1) > totalRows)
	{
		currentRowIndex = 1;
	}
	else
	{
		currentRowIndex++;
	}
	setShopScreen(currentRowIndex);
}

void UShopHUD::previousAsset()
{
	if ((currentRowIndex - 1) < 1)
	{
		currentRowIndex = totalRows;
	}
	else
	{
		currentRowIndex--;
	}
	setShopScreen(currentRowIndex);
}

void UShopHUD::setupSpawnTrackArray()
{
	//Handled in blueprint
	
}

void UShopHUD::purchasingCheck(int requiredFunds, int requiredLevel)
{
	bool canSpawn = false;

	if (requiredLevel <= GMref->GetCurLevel())
	{
		if (requiredFunds <= GMref->GetCurMoney())
		{
			for (int i = 0; i < tracksToSpawnObjects.Num(); i++)
			{
				canSpawn = spawnBoughtItem(i);
				if (canSpawn)
				{
					break;
				}
			}

			if (!canSpawn)
			{
				UE_LOG(LogTemp, Warning, TEXT("Area not clear cannot purchase Item"));
			}
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("Lacking Funds"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not high enough level"));
	}
}

bool UShopHUD::spawnBoughtItem(int passedIndex)
{
		bool spawnClear = false;

		if (tracksToSpawnObjects.IsValidIndex(passedIndex))
		{
			spawnClear = tracksToSpawnObjects[passedIndex]->checkObstruction();
		}

		if (spawnClear == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnedObject"));
			return spawnClear;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CannotSpawn"));
			return spawnClear;
		}
}