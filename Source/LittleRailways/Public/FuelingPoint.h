// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_Interact.h"
#include "FuelingPoint.generated.h"

UCLASS()
class LITTLERAILWAYS_API AFuelingPoint : public AActor, public IBPI_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelingPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FuelPoint", meta = (AllowPrivateAccess = "true"))
	//UBoxComponent* 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void consumeMaterial();

	void RefreshCoalAmount();

	void RefreshWaterAmount();

	void activated();

	void deactivated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void Interact(); void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FuelType")
	bool isWater;

	bool isActive;

	bool isFull = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FuelCapacity")
	float materialCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FuelCapacity")
	float currentMaterialLevel;

	FTimerHandle consumeTimer;
	FTimerHandle refreshTimer;
};
