// Fill out your copyright notice in the Description page of Project Settings.


#include "PassengerClass.h"

// Sets default values
APassengerClass::APassengerClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PassengerBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PassengerBody"));
	PassengerBody->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APassengerClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APassengerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

