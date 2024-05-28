// Fill out your copyright notice in the Description page of Project Settings.


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
	//TArray<AActor*> foundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawningTrack::StaticClass(), foundActors);

	//for (int i = 0; foundActors.Num(); i++)
	//{
	//	if (foundActors.IsValidIndex(i))
	//	{
	//		/*tracksToSpawnObjects.Add(Cast<ASpawningTrack>(foundActors[i]));*/
	//		UE_LOG(LogTemp, Warning, TEXT("ObjectAdded"));
	//	}
	//}
	//UE_LOG(LogTemp, Warning, TEXT("TrackArrayPopulated"));
}

void UShopHUD::spawnBoughtItem()
{
	bool canSpawn = false;

	for (int i = 0; tracksToSpawnObjects.Num(); i++)
	{
		if (tracksToSpawnObjects.IsValidIndex(i))
		{
			canSpawn = tracksToSpawnObjects[i]->checkObstruction();
			if (canSpawn)
			{
				UE_LOG(LogTemp, Warning, TEXT("SpawnedObject"));
				break;
			}
		}
	}

	if (!canSpawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("CannotSpawn"));
	}
}