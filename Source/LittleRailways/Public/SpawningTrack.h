// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawningTrack.generated.h"

UCLASS()
class LITTLERAILWAYS_API ASpawningTrack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TrackComponents", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* obstructionChecker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrackComponents")
	UStaticMeshComponent* railSegment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrackComponents")
	UStaticMeshComponent* ballastSegment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrackComponents")
	UStaticMeshComponent* emptyRoot;

	//Functions
	bool checkObstruction();
};
