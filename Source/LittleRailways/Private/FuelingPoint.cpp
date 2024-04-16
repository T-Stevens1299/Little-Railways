// Fill out your copyright notice in the Description page of Project Settings.


#include "FuelingPoint.h"

// Sets default values
AFuelingPoint::AFuelingPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFuelingPoint::BeginPlay()
{
	Super::BeginPlay();
	isActive = false;
	currentMaterialLevel = materialCapacity;
	if (isWater)
	{
		GetWorldTimerManager().SetTimer(refreshTimer, this, &AFuelingPoint::RefreshWaterAmount, 10.0f, true, 10.0f);
	}

	GetWorldTimerManager().SetTimer(consumeTimer, this, &AFuelingPoint::consumeMaterial, 5.0f, true, 5.0f);
	GetWorldTimerManager().PauseTimer(consumeTimer);
}

// Called every frame
void AFuelingPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFuelingPoint::Interact_Implementation()
{
	if (!isActive)
	{
		activated();
		UE_LOG(LogTemp, Warning, TEXT("Active"));
	}
	else
	{
		deactivated();
		UE_LOG(LogTemp, Warning, TEXT("Not Active"));
	}
}

void AFuelingPoint::activated()
{
	GetWorldTimerManager().UnPauseTimer(consumeTimer);
	isActive = true;
}

void AFuelingPoint::deactivated()
{
	GetWorldTimerManager().PauseTimer(consumeTimer);
	isActive = false;
}

void AFuelingPoint::consumeMaterial()
{
	isFull = false;
	UE_LOG(LogTemp, Warning, TEXT("ConsumeFuel"));
	currentMaterialLevel--;
}

void AFuelingPoint::RefreshCoalAmount()
{
	if (!isWater)
	{
		currentMaterialLevel = materialCapacity;
	}
}

void AFuelingPoint::RefreshWaterAmount()
{
	if (!isFull) 
	{
		if ((currentMaterialLevel + 1.0f) == materialCapacity)
		{
			currentMaterialLevel = materialCapacity;
			isFull = true;
			UE_LOG(LogTemp, Warning, TEXT("FuelRefreshed"));
		}
		else
		{
			currentMaterialLevel++;
			UE_LOG(LogTemp, Warning, TEXT("RefreshFuel"));
		}
	}
}
