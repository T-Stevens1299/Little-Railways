// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "SignalBoxControlsHUD.h"
#include "SignalBoxConsole.h"
#include "Components/Button.h"

USignalBoxControlsHUD::USignalBoxControlsHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void USignalBoxControlsHUD::NativeConstruct()
{
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &USignalBoxControlsHUD::closeWindow);
	}
}

void USignalBoxControlsHUD::SetPtr(ASignalBoxConsole *SBptr)
{
	SBref = SBptr;
}

void USignalBoxControlsHUD::setupPointStatus()
{
	pointStatus = SBref->getPointStatus();
	SetupMap();
}

bool USignalBoxControlsHUD::pointClicked(int arrayIndex)
{
	bool currentPointStatus = SBref->changeSelectedPoint(arrayIndex);
	return currentPointStatus;
}

void USignalBoxControlsHUD::closeWindow()
{
	SBref->closeHUD();
}