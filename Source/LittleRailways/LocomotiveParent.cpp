// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotiveParent.h"

// Sets default values
ALocomotiveParent::ALocomotiveParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocoBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	LocoBody->SetupAttachment(GetRootComponent());

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentA"));
	LeftWheel1->SetupAttachment(LocoBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentB"));
	LeftWheel2->SetupAttachment(LocoBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentC"));
	RightWheel1->SetupAttachment(LocoBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentD"));
	RightWheel2->SetupAttachment(LocoBody);

	BrakeMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("BrakeComponent"));
	BrakeMesh->SetupAttachment(LocoBody);
}

// Called when the game starts or when spawned
void ALocomotiveParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocomotiveParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (throttleOn == true)
	{
		LeftWheel1->AddTorqueInDegrees(FVector(0.0f, 50000000.0f, 0.0f));
		LeftWheel2->AddTorqueInDegrees(FVector(0.0f, 50000000.0f, 0.0f));
		RightWheel1->AddTorqueInDegrees(FVector(0.0f, 50000000.0f, 0.0f));
		RightWheel2->AddTorqueInDegrees(FVector(0.0f, 50000000.0f, 0.0f));
	}
}

void ALocomotiveParent::ApplyTorque() 
{
	if (throttleOn == true) 
	{
		throttleOn = false;
	}
	else
	{
		throttleOn = true;
	}
}

void ALocomotiveParent::ApplyBrakes(int passedBrakeVal)
{
	float brakeVal = passedBrakeVal;

	LeftWheel1->SetAngularDamping(brakeVal);
	LeftWheel2->SetAngularDamping(brakeVal);
	RightWheel1->SetAngularDamping(brakeVal);
	RightWheel2->SetAngularDamping(brakeVal);
}

void ALocomotiveParent::Brake_Implementation(int passedForce)
{
	ApplyBrakes(passedForce);
}
