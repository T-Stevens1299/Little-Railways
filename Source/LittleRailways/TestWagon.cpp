// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWagon.h"

// Sets default values
ATestWagon::ATestWagon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WagonBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wagon Body"));
	WagonBody->SetupAttachment(GetRootComponent());

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Wheel 1"));
	LeftWheel1->SetupAttachment(WagonBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Wheel 2"));
	LeftWheel2->SetupAttachment(WagonBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Wheel 1"));
	RightWheel1->SetupAttachment(WagonBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Wheel 2"));
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

