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
	downPlatformChecker->OnComponentBeginOverlap.AddDynamic(this, &AStationClass::downBeginOverlap);

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
	loadPassengers(true);
}

void AStationClass::downBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	loadPassengers(false);
}

void AStationClass::loadPassengers(bool IsUp)
{
	TArray<AActor*> overlappingActors;
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
					if (IsUp)
					{
						if (!((upPassengerTotal - 1) < 0))
						{
							carriageToCheck->loadPassengers(selectDestination(IsUp));
							upPassengerTotal--;
						}
					}
					else 
					{
						if (!((downPassengerTotal - 1) < 0))
						{
							carriageToCheck->loadPassengers(selectDestination(IsUp));
							downPassengerTotal--;
						}
					}
				}
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
			FActorSpawnParameters SpawnParams;
			downSpawnedPassengers.Add(GetWorld()->SpawnActor<APassengerClass>(spawnedActor, (GetActorLocation() + FVector(0.0f, 100.0f, 50.0f)), GetActorRotation(), SpawnParams));
			isUp = false;
		}
	}
	else
	{
		if (!((upPassengerTotal + 1) > upPassengerCapacity))
		{
			upPassengerTotal++;
			FActorSpawnParameters SpawnParams;
			upSpawnedPassengers.Add(GetWorld()->SpawnActor<APassengerClass>(spawnedActor, (GetActorLocation() + FVector(0.0f, -100.0f, 50.0f)), GetActorRotation(), SpawnParams));
			isUp = true;
		}
	}
}