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
}

// Called when the game starts or when spawned
void ATestWagon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestWagon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

