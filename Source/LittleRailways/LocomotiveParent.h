// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "BPI_Braking.h"
#include "LocomotiveParent.generated.h"

UCLASS()
class LITTLERAILWAYS_API ALocomotiveParent : public AActor, public IBPI_Braking
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocomotiveParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//Loco Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loco", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LocoBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loco", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loco", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loco", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loco", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loco", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* BrakeMesh;

	bool throttleOn = false;

public:
	//Functions
	UFUNCTION(BlueprintCallable, Category = "Loco")
	void ApplyTorque();

	void ApplyBrakes(int passedBrakeVal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Braking")
	void Brake(int passedForce); void Brake_Implementation(int passedForce) override;
};
