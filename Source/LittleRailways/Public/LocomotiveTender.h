// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "LocomotiveTender.generated.h"

UCLASS()
class LITTLERAILWAYS_API ALocomotiveTender : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocomotiveTender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions
	void consumeFuel(float fuelConsumed);

	void consumeWater(float waterConsumed);

	void increaseFuel(float fuelToAdd);

	void increaseWater(float waterToAdd);

	//Mesh Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tender", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TenderBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tender", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tender", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tender", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tender", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel2;

	//Fuel and water values

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float waterCapacity;

	float curWaterAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float fuelCapacity;

	float curFuelAmount;

	//Loco Ref
	class ALocoController* TrainRef;

	void SetTrainPtr(ALocoController* TrainPrt);
};
