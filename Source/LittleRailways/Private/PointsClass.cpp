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

	StraightColBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("SCB1Component"));
	StraightColBox1->SetupAttachment(Ballast);

	StraightColBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("SCB2Component"));
	StraightColBox2->SetupAttachment(Ballast);
}

// Called when the game starts or when spawned
void APointsClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointsClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

