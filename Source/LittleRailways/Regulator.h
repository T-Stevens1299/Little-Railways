// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Regulator.generated.h"

UCLASS()
class LITTLERAILWAYS_API ARegulator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARegulator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "regulator", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* InteractableMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "regulator", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* OutlineMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "regulator", meta = (AllowPrivateAccess = "true"))
	TArray<float> angleSettings;

protected:
	int curDetents;
	int totDetents = 4;

public:
	UFUNCTION(BlueprintCallable, Category = "regulator")
	void moveRegulator();

	void engageRegulator(int currentDetent);

	class ALocoController* TrainRef;

	void SetTrainPtr(ALocoController* TrainPrt);
};
