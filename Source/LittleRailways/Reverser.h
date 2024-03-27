// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Reverser.generated.h"

UCLASS()
class LITTLERAILWAYS_API AReverser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReverser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "reverser", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* InteractableMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "reverser", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* OutlineMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "reverser", meta = (AllowPrivateAccess = "true"))
	TArray<float> angleSettings;

protected:
	int curDetents;
	int totDetents = 2;

public:
	UFUNCTION(BlueprintCallable, Category = "reverser")
	void moveReverser();

	void setReverser(int currentDetent);

	class ALocoController* TrainRef;

	void SetTrainPtr(ALocoController* TrainPrt);
};
