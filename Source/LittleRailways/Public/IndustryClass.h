// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "IndustryClass.generated.h"

class AIndustryWagonLoader;

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

	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildingParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BuildingCore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LoadingDock", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LoadingDock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UnloadingDock", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* UnloadingDock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LoadingDevice", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* LoadingDevice;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	bool requiresInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int productAminRequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int productBminRequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int outputProduct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int inputProductA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int inputProductB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int productaPayout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int productbPayout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int productaXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	int productbXP;

	//Functions
	void destroyProductActor();

	void generateProduct();

	void increaseOutputProduct();

	void LoadProduct();

	void increaseMoneyXP(int passedMoney, int passedXP);

	UFUNCTION(BlueprintCallable, Category = "ProductTest")
	void increaseProductA();

	UFUNCTION(BlueprintCallable, Category = "ProductTest")
	void increaseProductB();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//References
	FTimerHandle productGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	TSubclassOf<AActor> productActorA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	TSubclassOf<AActor> productActorB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProductManagement")
	TSubclassOf<AActor> generatedProductWagon;

	UPROPERTY(BlueprintReadOnly, Category = "LoadingDevice")
	AIndustryWagonLoader* WagonLoaderComponent;

	AActor* actorToDestroy;

	class ALittleRailwaysGameMode* gmRef;
};