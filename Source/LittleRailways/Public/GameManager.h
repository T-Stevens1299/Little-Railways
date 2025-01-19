// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class LITTLERAILWAYS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void increaseMoney(int passedMoney);

	void increaseXP(int passedXP);

	void checkLevelUp();

	int32 currentXP;

	int currentMoney;

	int currentLevel;

	TArray<int32> xpLevelCaps;
};
