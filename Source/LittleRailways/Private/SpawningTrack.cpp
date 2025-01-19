// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


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
		UE_LOG(LogTemp, Warning, TEXT("Not Clear"));
		return false;
	}
}

void ASpawningTrack::spawnPurchasedItem(TSubclassOf<AActor> itemToSpawn)
{
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(itemToSpawn, (GetActorLocation() + FVector(0.0f, 0.0f, 200.0f)), GetActorRotation(), SpawnParams);
}