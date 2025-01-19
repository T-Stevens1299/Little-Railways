// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BPI_Interact.h"
#include "PointsClass.generated.h"

UCLASS()
class LITTLERAILWAYS_API APointsClass : public AActor, public IBPI_Interact
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


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StraightCollision", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StraightCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CurvedTrackCollision", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CurvedCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch")
	bool isStraight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch")
	bool debugOn;

	UFUNCTION(BlueprintCallable)
	void changePoints();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void Interact(); void Interact_Implementation() override;

protected:
	FVector hidden = FVector(0.0f, 0.0f, -200.0f);
	FVector active = FVector(0.0f, 0.0f, 0.0f);

	FVector straight = FVector(0.0f, -5.0f, 0.0f);
	FVector curved = FVector(0.0f, 10.0f, 0.0f);

	FRotator straightRot = FRotator(0.0f, 0.5f, 0.0f);
	FRotator curvedRot = FRotator(0.0f, -1.0f, 0.0f);
};