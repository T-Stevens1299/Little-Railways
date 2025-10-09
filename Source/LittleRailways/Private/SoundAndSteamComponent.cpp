// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundAndSteamComponent.h"
#include "LocoDrivers.h"
#include "LocoController.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USoundAndSteamComponent::USoundAndSteamComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USoundAndSteamComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USoundAndSteamComponent::setComponentVariables(ALocoController* LocoControl, ALocoDrivers* Drivers, UNiagaraComponent* SteamGen, UAudioComponent* LocoSound1, UAudioComponent* LocoSound2)
{
	locoRef = LocoControl;
	driversRef = Drivers;
	steamGenRef = SteamGen;
	LocoChuff1 = LocoSound1;
	LocoChuff2 = LocoSound2;
	triggerSoundCalculations = true;
}

void USoundAndSteamComponent::playWhistle()
{
	UGameplayStatics::PlaySoundAtLocation(this, whistleType, locoRef->GetActorLocation());
}

void USoundAndSteamComponent::toggleStaticSteam()
{
	steamGenRef->SetFloatParameter(floatParameter, maxExhaustParticleSize);
	steamGenRef->SetVectorParameter(vectorParameter, exhaustVelocity);
}

void USoundAndSteamComponent::SoundCalculations()
{
	//Define Local Variables
	float curWheelRot = driversRef->GetWheelRotation();
	bool cycle1Started = false;
	bool cycle2Started = false;

	if (curPistonStroke >= 2) { curPistonStroke = 0; }
	else
	{
		if (wheelDegreeFinder(curWheelRot))
		{
			if (!(cycle1Started || cycle2Started))
			{
				curPistonStroke += 1;
				if (curPistonStroke == 1)
				{
					LocoChuff2->Stop();
					LocoChuff1->Play();
					cycle1Started = true;
					cycle2Started = false;
				}
				else
				{
					LocoChuff1->Stop();
					LocoChuff2->Play();
					cycle1Started = false;
					cycle2Started = true;
				}
				steamGenRef->SetFloatParameter(floatParameter, maxSmokeParticleSize);
				steamGenRef->SetVectorParameter(vectorParameter, chuffVelocity);
			}
		}
		else
		{
			cycle1Started = false;
			cycle2Started = false;
			if (steamGenRef)
			{
				steamGenRef->SetFloatParameter(floatParameter, maxExhaustParticleSize);
				steamGenRef->SetVectorParameter(vectorParameter, exhaustVelocity);
			}
		}
	}
}

bool USoundAndSteamComponent::wheelDegreeFinder(float curWheelRot)
{
	bool condition1 = false;
	bool condition2 = false;

	if (curWheelRot < 60 && curWheelRot > 30) { condition1 = true; }
	if (curWheelRot < -30 && curWheelRot > -60) { condition2 = true; }

	return (condition1 || condition2);
}


// Called every frame
void USoundAndSteamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!triggerSoundCalculations) { return; }
	if (locoRef->throttleOn)
	{
		SoundCalculations();
	}
}