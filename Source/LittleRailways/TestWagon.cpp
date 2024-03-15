// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWagon.h"

// Sets default values
ATestWagon::ATestWagon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WagonBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	WagonBody->SetupAttachment(GetRootComponent());

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentA"));
	LeftWheel1->SetupAttachment(WagonBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentB"));
	LeftWheel2->SetupAttachment(WagonBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentC"));
	RightWheel1->SetupAttachment(WagonBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentD"));
	RightWheel2->SetupAttachment(WagonBody);

	FillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LoadComponent"));
	FillMesh->SetupAttachment(WagonBody);

	BrakeMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("BrakeComponent"));
	BrakeMesh->SetupAttachment(WagonBody);
}

// Called when the game starts or when spawned
void ATestWagon::BeginPlay()
{
	Super::BeginPlay();
	loadPercentage = 0;
	SetWagonLoad(loadPercentage);
}

// Called every frame
void ATestWagon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestWagon::LoadWagon() 
{
	if (loadPercentage < 100) 
	{
		loadPercentage = loadPercentage + 25;
		SetWagonLoad(loadPercentage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WagonFull"));
	}
}

void ATestWagon::SetWagonLoad(int loadPercent)
{
	for (int i = 0; i < 5; i++) 
	{
		if ((i * 25) == loadPercent) 
		{
			FillMesh->SetStaticMesh(LoadAmount[i]);
		}
	}
}

void ATestWagon::ApplyBrakes(int passedBrakeVal) 
{
	float brakeVal = passedBrakeVal;

	LeftWheel1->SetAngularDamping(brakeVal);
	LeftWheel2->SetAngularDamping(brakeVal);
	RightWheel1->SetAngularDamping(brakeVal);
	RightWheel2->SetAngularDamping(brakeVal);
}

void ATestWagon::Brake_Implementation(int passedForce) 
{
	ApplyBrakes(passedForce);
}