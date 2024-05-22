// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PassengerClass.generated.h"

UCLASS()
class LITTLERAILWAYS_API APassengerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APassengerClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Mesh Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passenger", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PassengerBody;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	FString targetDestination;

	//Functions

};
