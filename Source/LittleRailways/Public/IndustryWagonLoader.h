// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_Interact.h"
#include "IndustryWagonLoader.generated.h"

UCLASS()
class LITTLERAILWAYS_API AIndustryWagonLoader : public AActor, public IBPI_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIndustryWagonLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LoadingMesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WagonLoadingMesh;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void Interact(); void Interact_Implementation() override;

	class AIndustryClass* industryRef;

	void SetIndustryPtr(AIndustryClass* indPtr);
};
