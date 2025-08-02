// Fill out your copyright notice in the Description page of Project Settings.

#include "WeatherSpawner.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWeatherSpawner::AWeatherSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	WeatherEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WeatherEffectComponent"));
	WeatherEffect->SetupAttachment(RootComponent);
}

void AWeatherSpawner::changeWeatherEffect()
{
	int randomWeatherToSelect = UKismetMathLibrary::RandomIntegerInRange(0, WeatherOptions.Num() - 1);
	if (WeatherOptions.IsValidIndex(randomWeatherToSelect))
	{
		WeatherEffect->SetAsset(WeatherOptions[randomWeatherToSelect]);
	}
}

// Called when the game starts or when spawned
void AWeatherSpawner::BeginPlay()
{
	Super::BeginPlay();
	changeWeatherEffect();
}

// Called every frame
void AWeatherSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}