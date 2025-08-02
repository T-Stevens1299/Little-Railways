// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherSpawner.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class LITTLERAILWAYS_API AWeatherSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeatherSpawner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weather", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* WeatherEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	TArray<UNiagaraSystem*> WeatherOptions;

	void changeWeatherEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};