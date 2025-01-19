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

	pointStatus.Init(NULL, 16);

	setPointStatus();

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
	HUD->setupPointStatus();
	HUD->AddToViewport();
	PC->bShowMouseCursor = true;
	PC->SetInputMode(FInputModeUIOnly());
}

void ASignalBoxConsole::closeHUD()
{
	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());
	HUD->RemoveFromParent();
}

bool ASignalBoxConsole::changeSelectedPoint(int arrayIndex)
{
	if (pointsToControl.IsValidIndex(arrayIndex))
	{
		pointsToControl[arrayIndex]->changePoints();
	}
	pointStatus[arrayIndex] = pointsToControl[arrayIndex]->isStraight;
	return pointStatus[arrayIndex];
}

void ASignalBoxConsole::setPointStatus()
{
	for (int i = 0; i < pointsToControl.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoopRun"));
		if (pointsToControl.IsValidIndex(i))
		{
			UE_LOG(LogTemp, Warning, TEXT("FirstConditionMet"));
			if (pointStatus.IsValidIndex(i))
			{
				pointStatus[i] = pointsToControl[i]->isStraight;
				UE_LOG(LogTemp, Warning, TEXT("PointStatusSet"));
			}
		}
	}
}