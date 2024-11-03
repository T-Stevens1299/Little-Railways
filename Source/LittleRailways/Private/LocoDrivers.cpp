// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "LocoDrivers.h"

// Sets default values
ALocoDrivers::ALocoDrivers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	FrameBody->SetupAttachment(GetRootComponent());

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponent1"));
	LeftWheel1->SetupAttachment(FrameBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponent2"));
	LeftWheel2->SetupAttachment(FrameBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponent3"));
	RightWheel1->SetupAttachment(FrameBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponent4"));
	RightWheel2->SetupAttachment(FrameBody);

	ConRod1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConRodComponent1"));
	ConRod1->SetupAttachment(FrameBody);

	ConRod2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConRodComponent2"));
	ConRod2->SetupAttachment(FrameBody);

	Coupling = CreateDefaultSubobject<UChildActorComponent>(TEXT("CouplingComponent"));
	Coupling->SetupAttachment(FrameBody);

	Coupling2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("CouplingComponent2"));
	Coupling2->SetupAttachment(FrameBody);
}

// Called when the game starts or when spawned
void ALocoDrivers::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALocoDrivers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocoDrivers::ApplyTorque(int passedTorqueMultiplier)
{
	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), passedTorqueMultiplier);
	for (int i = 0; i < wheelsToDrive.Num(); i++)
	{
		switch (passedTorqueMultiplier)
		{
		case -100:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage4Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage4"));
			break;
		case -75:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage3Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage3"));
			break;
		case -50:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage2Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage2"));
			break;
		case -25:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage1Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage1"));
			break;
		case 100:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage4Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage4"));
			break;
		case 75:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage3Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage3"));
			break;
		case 50:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage2Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage2"));
			break;
		case 25:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage1Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Stage1"));
			break;
		default:
			wheelsToDrive[i]->SetPhysicsMaxAngularVelocityInRadians(Stage4Speed, false);
			UE_LOG(LogTemp, Warning, TEXT("Default"));
			break;
		}

		wheelsToDrive[i]->AddTorqueInRadians(FVector(0.0f, (passedTorqueMultiplier * TractiveTorque), 0.0f));
	}
}

void ALocoDrivers::ApplyBreaks(int passedBrakeVal)
{
	float brakeVal = passedBrakeVal;

	for (int i = 0; i < wheelsToDrive.Num(); i++)
	{
		wheelsToDrive[i]->SetAngularDamping(brakeVal);
	}
}

void ALocoDrivers::SetTrainPtr(ALocoController* TrainPrt)
{
	TrainRef = TrainPrt;
}