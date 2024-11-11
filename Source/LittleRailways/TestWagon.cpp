// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "TestWagon.h"

// Sets default values
ATestWagon::ATestWagon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WagonBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	WagonBody->SetupAttachment(GetRootComponent());

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentA"));
	LeftWheel1->SetupAttachment(WagonBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentB"));
	LeftWheel2->SetupAttachment(WagonBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentC"));
	RightWheel1->SetupAttachment(WagonBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentD"));
	RightWheel2->SetupAttachment(WagonBody);

	FillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LoadComponent"));
	FillMesh->SetupAttachment(WagonBody);

	BrakeMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("BrakeComponent"));
	BrakeMesh->SetupAttachment(WagonBody);
}

// Called when the game starts or when spawned
void ATestWagon::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(unloadTimer, this, &ATestWagon::UnloadWagon, 2.0f, true, 2.0f);
	GetWorldTimerManager().PauseTimer(unloadTimer);

	isUnloading = false;
}

// Called every frame
void ATestWagon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestWagon::LoadWagon() 
{
	//if (currentLoad + 1 <= totalLoad)
	//{
		currentLoad++;
		SetWagonLoad(currentLoad);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("WagonFull"));
	//}
}

void ATestWagon::UnloadWagon()
{
	if ((currentLoad - 1) == 0)
	{
		GetWorldTimerManager().PauseTimer(unloadTimer);
		isUnloading = false;
		UE_LOG(LogTemp, Warning, TEXT("StoppedLoading"));
	}
	currentLoad--;
	SetWagonLoad(currentLoad);
	SpawnLoadActor();
}

void ATestWagon::SetWagonLoad(int CurrentLoad)
{
	FillMesh->SetStaticMesh(LoadAmount[CurrentLoad]);
}

void ATestWagon::SpawnLoadActor()
{
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(spawnedActor, (GetActorLocation() + FVector(0.0f, 200.0f, 200.0f)), GetActorRotation(), SpawnParams);
}

void ATestWagon::ApplyBrakes(int passedBrakeVal) 
{
	float brakeVal = passedBrakeVal;

	LeftWheel1->SetAngularDamping(brakeVal);
	LeftWheel2->SetAngularDamping(brakeVal);
	RightWheel1->SetAngularDamping(brakeVal);
	RightWheel2->SetAngularDamping(brakeVal);
}

void ATestWagon::Brake_Implementation(int passedForce) 
{
	ApplyBrakes(passedForce);
}

void ATestWagon::Interact_Implementation()
{
	if (currentLoad == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WagonEmpty"));
	}
	else if (!isUnloading)
	{
		GetWorldTimerManager().UnPauseTimer(unloadTimer);
		isUnloading = true;
		UE_LOG(LogTemp, Warning, TEXT("WagonUnloading"));
	}
}