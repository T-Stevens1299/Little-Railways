// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StationClass.generated.h"

class APassengerClass;

UCLASS()
class LITTLERAILWAYS_API AStationClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStationClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildingParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BuildingCore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "upPlatform", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* upPlatformCatchmentZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "downPlatform", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* downPlatformCatchmentZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "upPlatform", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* upPlatformChecker;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "downPlatform", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* downPlatformChecker;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	TArray<UChildActorComponent*> upSpawnedPassengers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	TArray<UChildActorComponent*> downSpawnedPassengers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	TArray<FString> upDestinations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	TArray<FString> downDestinations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int upPassengerCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int downPassengerCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int upPassengerTotal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	int downPassengerTotal;

	bool isUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	TSubclassOf<APassengerClass> spawnedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	FString stationName;

	FTimerHandle passengerSpawner;

	//Functions
	void spawnPassengers();

	UFUNCTION()
	void upBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void downBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	

	UFUNCTION()
	void upEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void downEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void loadPassengers(bool IsUp);

	void unloadPassengers();

	void togglePassengerVisibility(int passedIndex, bool direction);

	FString selectDestination(bool isDown);

};