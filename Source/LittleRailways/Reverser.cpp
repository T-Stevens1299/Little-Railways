// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "Reverser.h"
#include "BPI_Braking.h"
#include "LocoController.h"

// Sets default values
AReverser::AReverser()
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
void AReverser::BeginPlay()
{
	Super::BeginPlay();
	curDetents = 1;
}

// Called every frame
void AReverser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReverser::moveReverser() 
{
	if (curDetents == 2) 
	{
		curDetents = 0;
	}
	else 
	{
		curDetents++;
	}

	setReverser(curDetents);
}

void AReverser::setReverser(int currentDetent) 
{
	for (int i = 0; i < 3; i++)
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
				BrakingInterface->Execute_SetReverser(GetParentActor(), currentDetent);
			}
		}
	}
}

void AReverser::SetTrainPtr(ALocoController *TrainPrt) 
{
	TrainRef = TrainPrt;
}