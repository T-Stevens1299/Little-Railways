// Fill out your copyright notice in the Description page of Project Settings.


#include "IndustryWagonLoader.h"
#include "IndustryClass.h"

// Sets default values
AIndustryWagonLoader::AIndustryWagonLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WagonLoadingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	WagonLoadingMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AIndustryWagonLoader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndustryWagonLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIndustryWagonLoader::Interact_Implementation()
{
	industryRef->LoadProduct();
}

void AIndustryWagonLoader::SetIndustryPtr(AIndustryClass* indPtr)
{
	industryRef = indPtr;
}