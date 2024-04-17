// Fill out your copyright notice in the Description page of Project Settings.


#include "IndustryClass.h"

// Sets default values
AIndustryClass::AIndustryClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIndustryClass::BeginPlay()
{
	Super::BeginPlay();
	
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
	UE_LOG(LogTemp, Warning, TEXT("AInputIncreased"));
}

void AIndustryClass::increaseProductB()
{
	inputProductB++;
	UE_LOG(LogTemp, Warning, TEXT("BInputIncreased"));
}