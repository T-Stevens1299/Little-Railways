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

	RegulatorMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("RegComponent"));
	RegulatorMesh->SetupAttachment(LocoBody);

	ReverserMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("ReverserComponent"));
	ReverserMesh->SetupAttachment(LocoBody);
}

// Called when the game starts or when spawned
void ALocomotiveParent::BeginPlay()
{
	Super::BeginPlay();
	passedTorqueMulti = 0;
}

// Called every frame
void ALocomotiveParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (canMove == true)
	{
		if (throttleOn == true)
		{
			if (isReversing == false)
			{
				LeftWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
				LeftWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
				RightWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
				RightWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
			}
			else
			{
				LeftWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
				LeftWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
				RightWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
				RightWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
			}
		}
	}

	float speed = ((GetVelocity().Size2D() * 3600) / 100000);
	FString speedOutput = FString::SanitizeFloat(speed);
	
	if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *speedOutput);
	}


}

void ALocomotiveParent::ApplyTorque(int passedTorqueMultiplier)
{
		passedTorqueMulti = passedTorqueMultiplier;
		if (passedTorqueMulti != 0) 
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

void ALocomotiveParent::Regulator_Implementation(int passedTorque)
{
	throttleOn = false;
	ApplyTorque(passedTorque);
}

void ALocomotiveParent::SetReverser_Implementation(int passedDetent)
{
	if (passedDetent == 0)
	{
		isReversing = true;
		canMove = true;
	}
	else if (passedDetent == 2) 
	{
		isReversing = false;
		canMove = true;
	}
	else if (passedDetent == 1) 
	{
		canMove = false;
	}
}