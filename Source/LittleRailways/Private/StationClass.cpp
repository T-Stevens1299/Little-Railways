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

	GetWorldTimerManager().SetTimer(passengerSpawner, this, &AStationClass::spawnPassengers, 10.0f, true, 10.0f);
}

// Called every frame
void AStationClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStationClass::upBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AStationClass::downBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

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