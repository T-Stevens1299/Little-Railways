// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsClass.h"

// Sets default values
APointsClass::APointsClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ballast = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallastComponent"));
	Ballast->SetupAttachment(GetRootComponent());

	Sleepers = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SleeperComponent"));
	Sleepers->SetupAttachment(Ballast);

	OuterRails = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OuterRailsComponent"));
	OuterRails->SetupAttachment(Ballast);

	GuideRails = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GuideRailsComponent"));
	GuideRails->SetupAttachment(Ballast);

	SwitchRails = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchRailsComponent"));
	SwitchRails->SetupAttachment(Ballast);

	StraightCollision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StraightCollisionComponent"));
	StraightCollision->SetupAttachment(Ballast);

	CurvedCollision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurvedCollisionComponent"));
	CurvedCollision->SetupAttachment(Ballast);
}

// Called when the game starts or when spawned
void APointsClass::BeginPlay()
{
	Super::BeginPlay();
	changePoints();
}

// Called every frame
void APointsClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointsClass::Interact_Implementation()
{
	changePoints();
}

//Switches the points depending on their current direction
void APointsClass::changePoints()
{
	if (isStraight)
	{
		StraightCollision->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
		CurvedCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		isStraight = false;
	}
	else
	{
		CurvedCollision->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
		StraightCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		isStraight = true;
	}
}