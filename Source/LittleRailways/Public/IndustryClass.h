// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IndustryClass.generated.h"

UCLASS()
class LITTLERAILWAYS_API AIndustryClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIndustryClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	bool requiresInput;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productAminRequiredAmount;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productBminRequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int outputProduct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int inputProductA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int inputProductB;

	void generateProduct();

	void increaseOutputProduct();

	UFUNCTION(BlueprintCallable, Category = "ProductTest")
	void increaseProductA();

	UFUNCTION(BlueprintCallable, Category = "ProductTest")
	void increaseProductB();

	FTimerHandle productGeneration;

};