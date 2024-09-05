// Fill out your copyright notice in the Description page of Project Settings.


#include "Coupling.h"

// Sets default values
ACoupling::ACoupling()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CouplingHolder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CouplingHolderComponent"));
	CouplingHolder->SetupAttachment(GetRootComponent());

	CouplingBuffer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CouplingBufferComponent"));
	CouplingBuffer->SetupAttachment(CouplingHolder);

	CouplingBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CouplingBarComponent"));
	CouplingBar->SetupAttachment(CouplingHolder);

	CouplingRod = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CouplingRodComponent"));
	CouplingRod->SetupAttachment(CouplingBar);

	OverlapChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapChecker->SetupAttachment(CouplingHolder);
}

// Called when the game starts or when spawned
void ACoupling::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoupling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoupling::Interact_Implementation()
{
	MoveCoupling();
}

void ACoupling::MoveCoupling()
{
	UE_LOG(LogTemp, Warning, TEXT("CouplingMoved"));
}