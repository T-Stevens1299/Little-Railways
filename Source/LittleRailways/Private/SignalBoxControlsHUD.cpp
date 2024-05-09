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

}

void USignalBoxControlsHUD::SetPtr(ASignalBoxConsole *SBptr)
{
	SBref = SBptr;
}

void USignalBoxControlsHUD::setPointsOnMap()
{
	pointStatus = SBref->getPointStatus();
}

void USignalBoxControlsHUD::pointClicked(int arrayIndex)
{
	SBref->changeSelectedPoint(arrayIndex);
}