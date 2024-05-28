// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningTrack.h"

// Sets default values
ASpawningTrack::ASpawningTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	emptyRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("emptyRootComponent"));
	emptyRoot->SetupAttachment(GetRootComponent());

	railSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("railSegmentComponent"));
	railSegment->SetupAttachment(emptyRoot);

	ballastSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ballastSegmentComponent"));
	ballastSegment->SetupAttachment(emptyRoot);

	obstructionChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("obstructionCheckerComponent"));
	obstructionChecker->SetupAttachment(emptyRoot);
}

// Called when the game starts or when spawned
void ASpawningTrack::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawningTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawningTrack::checkObstruction()
{
	TArray<AActor*> overlappingActors;
	obstructionChecker->GetOverlappingActors(overlappingActors);

	if (overlappingActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear"));
		return true;
	}
	else
	{
		return false;
	}
}