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
	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	bool requiresInput;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productAminRequiredAmount;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productBminRequiredAmount;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int outputProduct;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int inputProductA;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int inputProductB;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productaPayout;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productbPayout;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
	int productaXP;

	UPROPERTY(EditDefaultsOnly, Category = "ProductManagement")
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