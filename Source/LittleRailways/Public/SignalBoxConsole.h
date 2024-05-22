// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_Interact.h"
#include "SignalBoxConsole.generated.h"

class APointsClass;

UCLASS()
class LITTLERAILWAYS_API ASignalBoxConsole : public AActor, public IBPI_Interact
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASignalBoxConsole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Console", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConsoleMesh;

	//Functions
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void Interact(); void Interact_Implementation() override;

	void changeSelectedPoint(int arrayIndex);

	void setPointStatus();

	TArray<bool> getPointStatus() { return pointStatus; }

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsControlled")
	TArray<APointsClass*> pointsToControl;
	
	UPROPERTY()
	TArray<bool> pointStatus;

protected:
	/** HUD Widget */
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> HUDref;

	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class USignalBoxControlsHUD* HUD;

	APlayerController* PC;
};