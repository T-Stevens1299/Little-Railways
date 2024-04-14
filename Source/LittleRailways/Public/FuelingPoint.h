// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuelingPoint.generated.h"

UCLASS()
class LITTLERAILWAYS_API AFuelingPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelingPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void consumeMaterial();

	void RefreshCoalAmount();

	void RefreshWaterAmount();

	void activated();

	void deactivated();

	UFUNCTION(BlueprintCallable)
	void onClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FuelType")
	bool isWater;

	bool isActive;

	bool isFull = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FuelCapacity")
	float materialCapacity;

	float currentMaterialLevel;

	FTimerHandle consumeTimer;
	FTimerHandle refreshTimer;
};
