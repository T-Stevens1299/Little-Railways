// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PointsClass.generated.h"

UCLASS()
class LITTLERAILWAYS_API APointsClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointsClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PointsBallast", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Ballast;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PointsSleepers", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Sleepers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PointsOuterRails", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* OuterRails;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PointsGuideRails", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GuideRails;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PointsSwitchRails", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SwitchRails;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StraightCollisionA", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* StraightColBox1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StraightCollisionB", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* StraightColBox2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CurvedTrackCollision")
	TArray<UBoxComponent*> curvedTrackCollisionBoxes;
};
