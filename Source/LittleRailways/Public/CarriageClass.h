// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarriageClass.generated.h"

class APassengerClass;

UCLASS()
class LITTLERAILWAYS_API ACarriageClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarriageClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Mesh Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carriage", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CarriageBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carriage", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carriage", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carriage", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carriage", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel2;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int passengerCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int currentPassengerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int luxuryMultiplier;

	FString currentDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	TArray<FString> passengerDestinations;

	class ALittleRailwaysGameMode* gmRef;


	//Functions
	void loadPassengers(FString destination);

	void unloadPassengers();

	void setDestination(FString curDest);

	void addMoneyAndXP();

	void spawnPassengersOnPlatform(int passedIndex);

};