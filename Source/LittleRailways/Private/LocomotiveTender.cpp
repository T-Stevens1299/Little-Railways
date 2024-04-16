// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotiveTender.h"

// Sets default values
ALocomotiveTender::ALocomotiveTender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TenderBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	TenderBody->SetupAttachment(GetRootComponent());

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentA"));
	LeftWheel1->SetupAttachment(TenderBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentB"));
	LeftWheel2->SetupAttachment(TenderBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentC"));
	RightWheel1->SetupAttachment(TenderBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentD"));
	RightWheel2->SetupAttachment(TenderBody);

}

// Called when the game starts or when spawned
void ALocomotiveTender::BeginPlay()
{
	Super::BeginPlay();
	
	curFuelAmount = 0;

	curWaterAmount = 0;

}

// Called every frame
void ALocomotiveTender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocomotiveTender::consumeFuel(float fuelConsumed)
{
	if (curFuelAmount - fuelConsumed <= 0)
	{
		curFuelAmount = 0;
	}
	else
	{
		curFuelAmount = curFuelAmount - fuelConsumed;
	}
}

void ALocomotiveTender::consumeWater(float waterConsumed)
{
	if (curWaterAmount - waterConsumed <= 0)
	{
		curWaterAmount = 0;
	}
	else
	{
		curWaterAmount = curWaterAmount - waterConsumed;
	}
}

void ALocomotiveTender::increaseFuel(float fuelToAdd)
{
	if (curFuelAmount < fuelCapacity)
	{
		if (curFuelAmount + fuelToAdd <= fuelCapacity)
		{
			curFuelAmount = curFuelAmount + fuelToAdd;
		}
		else
		{
			curFuelAmount = fuelCapacity;
		}
		UE_LOG(LogTemp, Warning, TEXT("CoalIncreased"));
	}
}

void ALocomotiveTender::increaseWater(float waterToAdd)
{
	if (curWaterAmount < waterCapacity)
	{
		if (curWaterAmount + waterToAdd <= waterCapacity)
		{
			curWaterAmount = curWaterAmount + waterToAdd;
		}
		else
		{
			curWaterAmount = waterCapacity;
		}
		UE_LOG(LogTemp, Warning, TEXT("WaterIncreased"));
	}
}

void ALocomotiveTender::SetTrainPtr(ALocoController* TrainPrt)
{
	TrainRef = TrainPrt;
}