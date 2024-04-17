// Fill out your copyright notice in the Description page of Project Settings.


#include "IndustryClass.h"
#include "IndustryWagonLoader.h"
#include "LittleRailways/LittleRailwaysGameMode.h"
#include "LittleRailways/TestWagon.h"
#include "BPI_StatsIncrease.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AIndustryClass::AIndustryClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingCore = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingComponent"));
	BuildingCore->SetupAttachment(GetRootComponent());

	LoadingDock = CreateDefaultSubobject<UBoxComponent>(TEXT("LoadingComponent"));
	LoadingDock->SetupAttachment(BuildingCore);

	UnloadingDock = CreateDefaultSubobject<UBoxComponent>(TEXT("UnloadingComponent"));
	UnloadingDock->SetupAttachment(BuildingCore);

	LoadingDevice = CreateDefaultSubobject<UChildActorComponent>(TEXT("LoadingDeviceComponent"));
	LoadingDevice->SetupAttachment(BuildingCore);
}

// Called when the game starts or when spawned
void AIndustryClass::BeginPlay()
{
	Super::BeginPlay();

	gmRef = Cast<ALittleRailwaysGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	WagonLoaderComponent = Cast<AIndustryWagonLoader>(LoadingDevice->GetChildActor());
	if (WagonLoaderComponent)
	{
		WagonLoaderComponent->SetIndustryPtr(this);
	}

	UnloadingDock->OnComponentBeginOverlap.AddDynamic(this, &AIndustryClass::BeginOverlap);

	GetWorldTimerManager().SetTimer(productGeneration, this, &AIndustryClass::generateProduct, 10.0f, true, 10.0f);
}

// Called every frame
void AIndustryClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIndustryClass::generateProduct()
{
	if (requiresInput)
	{
		int productAremains = inputProductA - productAminRequiredAmount;
		int productBremains = inputProductB - productBminRequiredAmount;

		if (!(productAremains < 0) && !(productBremains < 0))
		{
			inputProductA = inputProductA - productAminRequiredAmount;
			inputProductB = inputProductB - productBminRequiredAmount;
			increaseOutputProduct();
		}
	}
	else 
	{
		increaseOutputProduct();
	}
}

void AIndustryClass::increaseOutputProduct()
{
	outputProduct++;
	UE_LOG(LogTemp, Warning, TEXT("ProductGenerated"));
}

void AIndustryClass::increaseProductA()
{
	inputProductA++;
	increaseMoneyXP(productaPayout, productaXP);
	UE_LOG(LogTemp, Warning, TEXT("AInputIncreased"));
}

void AIndustryClass::increaseProductB()
{
	inputProductB++;
	increaseMoneyXP(productbPayout, productbXP);
	UE_LOG(LogTemp, Warning, TEXT("BInputIncreased"));
}

void AIndustryClass::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FTimerHandle UnusedHandle;
	TSubclassOf<AActor> overlappedActor = OtherActor->GetClass();
	if (overlappedActor == productActorA)
	{
		increaseProductA();
		actorToDestroy = OtherActor;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AIndustryClass::destroyProductActor, 0.5f, false);
	}
	else if (overlappedActor == productActorB)
	{
		increaseProductB();
		actorToDestroy = OtherActor;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AIndustryClass::destroyProductActor, 0.5f, false);
	}
}

void AIndustryClass::destroyProductActor()
{
	actorToDestroy->Destroy();
}

void AIndustryClass::LoadProduct()
{
	if (outputProduct != 0) 
	{
		TArray<AActor*> actorsToCheck;
		LoadingDock->GetOverlappingActors(actorsToCheck);
		for (int i = 0; i < actorsToCheck.Num(); i++)
		{
			TSubclassOf<AActor> actorToCheck = actorsToCheck[i]->GetClass();
			if (actorToCheck == generatedProductWagon)
			{
				ATestWagon* wagonRef = Cast<ATestWagon>(actorsToCheck[i]);
				wagonRef->LoadWagon();
				outputProduct--;
			}
		}
	}
}

void AIndustryClass::increaseMoneyXP(int passedMoney, int passedXP)
{
	IBPI_StatsIncrease* increaseStats = Cast<IBPI_StatsIncrease>(gmRef);
	if (increaseStats) 
	{
		increaseStats->Execute_addMoney(gmRef, passedMoney);
		increaseStats->Execute_addXP(gmRef, passedXP);
	}
}

//when child actor - wagonLoader - is interacted with call this function
//LoadProduct()
//check to see the overlapped wagon type
//if wagon type matches the variable - wagonTypeToLoad
//call LoadWagon on the overlapped wagon
//outputproduct--;