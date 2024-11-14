// Fill out your copyright notice in the Description page of Project Settings.


#include "StationClass.h"
#include "LocoController.h"
#include "PassengerClass.h"
#include "CarriageClass.h"

// Sets default values
AStationClass::AStationClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingCore = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	BuildingCore->SetupAttachment(GetRootComponent());

	upPlatformCatchmentZone = CreateDefaultSubobject<UBoxComponent>(TEXT("upCatchmentComponent"));
	upPlatformCatchmentZone->SetupAttachment(BuildingCore);

	downPlatformCatchmentZone = CreateDefaultSubobject<UBoxComponent>(TEXT("downCatchmentComponent"));
	downPlatformCatchmentZone->SetupAttachment(BuildingCore);

	upPlatformChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("upCheckerComponent"));
	upPlatformChecker->SetupAttachment(BuildingCore);

	downPlatformChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("downCheckerComponent"));
	downPlatformChecker->SetupAttachment(BuildingCore);
}

// Called when the game starts or when spawned
void AStationClass::BeginPlay()
{
	Super::BeginPlay();
	
	upPlatformChecker->OnComponentBeginOverlap.AddDynamic(this, &AStationClass::upBeginOverlap);
	upPlatformChecker->OnComponentEndOverlap.AddDynamic(this, &AStationClass::upEndOverlap);

	downPlatformChecker->OnComponentBeginOverlap.AddDynamic(this, &AStationClass::downBeginOverlap);
	downPlatformChecker->OnComponentEndOverlap.AddDynamic(this, &AStationClass::downEndOverlap);

	//Setup Timers
	GetWorldTimerManager().SetTimer(passengerSpawner, this, &AStationClass::spawnPassengers, 10.0f, true, 10.0f);
}

// Called every frame
void AStationClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStationClass::upBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALocoController* locoRef1 = Cast<ALocoController>(OtherActor);
	if (locoRef1)
	{
		locoRef1->togglePassengerButtons(true, this);
	}
}

void AStationClass::upEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALocoController* locoRef2 = Cast<ALocoController>(OtherActor);
	if (locoRef2)
	{
		locoRef2->togglePassengerButtons(true, this);
	}
}

void AStationClass::downBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALocoController* locoRef3 = Cast<ALocoController>(OtherActor);
	if (locoRef3)
	{
		locoRef3->togglePassengerButtons(false, this);
	}
}

void AStationClass::downEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALocoController* locoRef4 = Cast<ALocoController>(OtherActor);
	if (locoRef4)
	{
		locoRef4->togglePassengerButtons(false, this);
	}
}

void AStationClass::loadPassengers(bool IsUp)
{
	TArray<AActor*> overlappingActors;

	if (IsUp)
	{
		upPlatformCatchmentZone->GetOverlappingActors(overlappingActors);
		for (int i = 0; i < overlappingActors.Num(); i++)
		{
			ACarriageClass* carriageToCheck = Cast<ACarriageClass>(overlappingActors[i]);
			if (carriageToCheck)
			{
				for (int j = 0; j < carriageToCheck->passengerCapacity; j++)
				{
					if (!((carriageToCheck->currentPassengerCount + 1) > carriageToCheck->passengerCapacity))
					{
						if (!((upPassengerTotal - 1) < 0))
						{
							carriageToCheck->loadPassengers(selectDestination(IsUp));
							togglePassengerVisibility(upPassengerTotal - 1, IsUp);
							upPassengerTotal--;
							UE_LOG(LogTemp, Warning, TEXT("LoadPassengersUp"));
						}
					}
				}
			}
		}

	}
	else
	{
		downPlatformCatchmentZone->GetOverlappingActors(overlappingActors);
		for (int i = 0; i < overlappingActors.Num(); i++)
		{
			ACarriageClass* carriageToCheck = Cast<ACarriageClass>(overlappingActors[i]);
			if (carriageToCheck)
			{
				for (int j = 0; j < carriageToCheck->passengerCapacity; j++)
				{
					if (!((carriageToCheck->currentPassengerCount + 1) > carriageToCheck->passengerCapacity))
					{
						if (!((downPassengerTotal - 1) < 0))
						{
							carriageToCheck->loadPassengers(selectDestination(IsUp));
							togglePassengerVisibility(downPassengerTotal - 1, IsUp);
							downPassengerTotal--;
							UE_LOG(LogTemp, Warning, TEXT("LoadPassengersDown"));
						}
					}
				}
			}
		}
	}
}

void AStationClass::unloadPassengers(bool platformIdentifier)
{
	TArray<AActor*> overlappingActors;

	if (platformIdentifier)
	{
		upPlatformCatchmentZone->GetOverlappingActors(overlappingActors);
		for (int i = 0; i < overlappingActors.Num(); i++)
		{
			ACarriageClass* carriageToCheck = Cast<ACarriageClass>(overlappingActors[i]);
			if (carriageToCheck)
			{
				carriageToCheck->emptyPassengers(stationName);
				UE_LOG(LogTemp, Warning, TEXT("UnloadPassengersUp"));
			}
		}
	}
	else
	{
		downPlatformCatchmentZone->GetOverlappingActors(overlappingActors);
		for (int i = 0; i < overlappingActors.Num(); i++)
		{
			ACarriageClass* carriageToCheck = Cast<ACarriageClass>(overlappingActors[i]);
			if (carriageToCheck)
			{
				carriageToCheck->emptyPassengers(stationName);
				UE_LOG(LogTemp, Warning, TEXT("UnloadPassengersDown"));
			}
		}
	}
}

FString AStationClass::selectDestination(bool isDown)
{
	int chosenIndex;
	if (isDown)
	{
		chosenIndex = (rand() % downDestinations.Num());
		if (upDestinations.IsValidIndex(chosenIndex))
		{
			return downDestinations[chosenIndex];
		}
	}
	else
	{
		chosenIndex = (rand() % upDestinations.Num());
		if (upDestinations.IsValidIndex(chosenIndex))
		{
			return upDestinations[chosenIndex];
		}
	}
	return "";
}

//Deprecated - rewrite function
void AStationClass::spawnPassengers()
{
	if (isUp)
	{
		if (!((downPassengerTotal + 1) > downPassengerCapacity)) 
		{
			downPassengerTotal++;
			isUp = false;
			togglePassengerVisibility(downPassengerTotal - 1, isUp);
		}
	}
	else
	{
		if (!((upPassengerTotal + 1) > upPassengerCapacity))
		{
			upPassengerTotal++;
			isUp = true;
			togglePassengerVisibility(upPassengerTotal - 1, isUp);
		}
	}
}

void AStationClass::togglePassengerVisibility(int passedIndex, bool direction)
{
	if(direction)
	{
		if (upSpawnedPassengers.IsValidIndex(passedIndex))
		{
			if (upSpawnedPassengers[passedIndex]->bHiddenInGame)
			{
				upSpawnedPassengers[passedIndex]->SetHiddenInGame(false);
			}
			else
			{
				upSpawnedPassengers[passedIndex]->SetHiddenInGame(true);
			}
		}
	}
	else
	{
		if (downSpawnedPassengers.IsValidIndex(passedIndex))
		{
			if (downSpawnedPassengers[passedIndex]->bHiddenInGame)
			{
				downSpawnedPassengers[passedIndex]->SetHiddenInGame(false);

			}
			else
			{
				downSpawnedPassengers[passedIndex]->SetHiddenInGame(true);
			}
		}
	}
}