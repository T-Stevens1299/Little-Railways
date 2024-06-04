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
}

void UShopHUD::SetGMptr(ALittleRailwaysGameMode* GMptr)
{
	GMref = GMptr;
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//setupSpawnTrackArray();
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

void UShopHUD::setupSpawnTrackArray()
{
	//Handled in blueprint
}

void UShopHUD::purchasingCheck()
{
	bool canSpawn = false;

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