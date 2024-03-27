// Fill out your copyright notice in the Description page of Project Settings.


#include "Regulator.h"
#include "BPI_Braking.h"
#include "LocoController.h"

// Sets default values
ARegulator::ARegulator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableComponent"));
	InteractableMeshComponent->SetupAttachment(RootComponent);

	OutlineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineComponent"));
	OutlineMeshComponent->SetupAttachment(InteractableMeshComponent);

	InteractableMeshComponent->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void ARegulator::BeginPlay()
{
	Super::BeginPlay();
	curDetents = 0;
}

// Called every frame
void ARegulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARegulator::moveRegulator() 
{
	if (curDetents == 4)
	{
		curDetents = 0;
	}
	else
	{
		curDetents++;
	}

	engageRegulator(curDetents);
}

void ARegulator::engageRegulator(int currentDetent) 
{
	for (int i = 0; i < 5; i++)
	{
		if (i == currentDetent)
		{
			FRotator newRot;
			newRot.Yaw = 0.0f;
			newRot.Pitch = angleSettings[i];
			newRot.Roll = 0.0f;

			InteractableMeshComponent->SetWorldRotation(newRot);

			IBPI_Braking* BrakingInterface = Cast<IBPI_Braking>(GetParentActor());
			if (BrakingInterface)
			{
				BrakingInterface->Execute_Regulator(GetParentActor(), currentDetent * 25);
			}
		}
	}
}

void ARegulator::SetTrainPtr(ALocoController* TrainPrt)
{
	TrainRef = TrainPrt;
}