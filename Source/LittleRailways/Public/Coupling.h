// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_Interact.h"
#include "Coupling.generated.h"

UCLASS()
class LITTLERAILWAYS_API ACoupling : public AActor, public IBPI_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoupling();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CouplingParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CouplingHolder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CouplingParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CouplingBuffer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CouplingParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CouplingBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CouplingParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CouplingRod;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void Interact(); void Interact_Implementation() override;

	void MoveCoupling();

	bool isCoupled;
};
