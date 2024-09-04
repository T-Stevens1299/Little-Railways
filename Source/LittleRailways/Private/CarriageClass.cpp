// Fill out your copyright notice in the Description page of Project Settings.


#include "CarriageClass.h"
#include "LittleRailways/LittleRailwaysGameMode.h"
#include "BPI_StatsIncrease.h"
#include "PassengerClass.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACarriageClass::ACarriageClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarriageBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	CarriageBody->SetupAttachment(GetRootComponent());

	Coupling1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coupling1Component"));
	Coupling1->SetupAttachment(CarriageBody);

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentA"));
	LeftWheel1->SetupAttachment(CarriageBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentB"));
	LeftWheel2->SetupAttachment(CarriageBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentC"));
	RightWheel1->SetupAttachment(CarriageBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentD"));
	RightWheel2->SetupAttachment(CarriageBody);
}

// Called when the game starts or when spawned
void ACarriageClass::BeginPlay()
{
	Super::BeginPlay();
	
	gmRef = Cast<ALittleRailwaysGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ACarriageClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACarriageClass::loadPassengers(FString destination)
{
	//Safety check to ensure the array does not exceed a certain size
	currentPassengerCount++;
	passengerDestinations.Add(destination);
}

void ACarriageClass::emptyPassengers(FString currentDestination)
{
	UE_LOG(LogTemp, Warning, TEXT("PassengersUnloaded"));
	if (currentPassengerCount != 0)
	{
		for (int i = passengerDestinations.Num(); i >= 0; i--)
		{
			if (passengerDestinations.IsValidIndex(i))
			{
				if (passengerDestinations[i] == currentDestination)
				{
					spawnPassengersOnPlatform(i);
					addMoneyAndXP();
				}
			}
		}
	}
}

void ACarriageClass::spawnPassengersOnPlatform(int passedIndex)
{
	passengerDestinations.RemoveAt(passedIndex);
	currentPassengerCount--;
	//Spawn Actor
}

void ACarriageClass::addMoneyAndXP()
{
	IBPI_StatsIncrease* increaseStats = Cast<IBPI_StatsIncrease>(gmRef);
	if (increaseStats)
	{
		increaseStats->Execute_addMoney(gmRef, (10 * luxuryMultiplier));
		increaseStats->Execute_addXP(gmRef, (10 * luxuryMultiplier));
	}
}