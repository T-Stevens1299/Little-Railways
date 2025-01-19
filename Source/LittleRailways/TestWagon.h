// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "BPI_Braking.h"
#include "Public/BPI_Interact.h"
#include "TestWagon.generated.h"

UCLASS()
class LITTLERAILWAYS_API ATestWagon : public AActor, public IBPI_Braking, public IBPI_Interact
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestWagon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//Mesh Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WagonBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FillMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> LoadAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wagon", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* BrakeMesh;

public:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadAmount")
	int currentLoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadAmount")
	int totalLoad;

	bool isUnloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnedActor")
	TSubclassOf<AActor> spawnedActor;

	FTimerHandle unloadTimer;


public:
	//Functions
	UFUNCTION(BlueprintCallable, Category = "Wagon")
	void LoadWagon();

	UFUNCTION(BlueprintCallable, Category = "Wagon")
	void UnloadWagon();

	void SpawnLoadActor();

	void SetWagonLoad(int CurrentLoad);

	void ApplyBrakes(int passedBrakeVal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Braking")
	void Brake(int passedForce); void Brake_Implementation(int passedForce) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void Interact(); void Interact_Implementation() override;

};
