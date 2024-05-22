// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#include "SignalBoxConsole.h"
#include "SignalBoxControlsHUD.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "PointsClass.h"

// Sets default values
ASignalBoxConsole::ASignalBoxConsole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConsoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConsoleComponent"));
	ConsoleMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASignalBoxConsole::BeginPlay()
{
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	HUD = CreateWidget<USignalBoxControlsHUD>(PC, HUDref);
	HUD->SetPtr(this);
}

// Called every frame
void ASignalBoxConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASignalBoxConsole::Interact_Implementation()
{
	HUD->setPointsOnMap();
	HUD->AddToViewport();
	PC->bShowMouseCursor = true;
}

void ASignalBoxConsole::changeSelectedPoint(int arrayIndex)
{
	if (pointsToControl.IsValidIndex(arrayIndex))
	{
		pointsToControl[arrayIndex]->changePoints();
	}

	setPointStatus();
}

void ASignalBoxConsole::setPointStatus()
{
	for (int i = 0; i < pointsToControl.Num(); i++)
	{
		if (pointsToControl.IsValidIndex(i) && pointStatus.IsValidIndex(i))
		{
			pointStatus[i] = pointsToControl[i]->isStraight;
		}
	}
}