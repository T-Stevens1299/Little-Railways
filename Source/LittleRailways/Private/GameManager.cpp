// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::increaseMoney(int passedMoney)
{
	currentMoney = currentMoney + passedMoney;
}

void AGameManager::increaseXP(int passedXP)
{
	currentXP = currentXP + passedXP;
	checkLevelUp();
}

void AGameManager::checkLevelUp()
{
	//for (int i = 0; i < xpLevelCaps->N; i++)
	//{
	//	currentXP += xpLevelCaps[i];
	//}
}