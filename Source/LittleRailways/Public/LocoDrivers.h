// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocoDrivers.generated.h"

UCLASS()
class LITTLERAILWAYS_API ALocoDrivers : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocoDrivers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrameBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConRod1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConRod2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Coupling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Coupling2;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TractionVariables")
	float TractiveTorque;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TractionVariables")
	float MaxSpeedKph;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TractionVariables")
	TArray<UStaticMeshComponent*> wheelsToDrive;


	//Functions
	void ApplyTorque(int passedTorqueMultiplier);

	void ApplyBreaks(int passedBrakeVal);

	//References
	class ALocoController* TrainRef;

	void SetTrainPtr(ALocoController* TrainPrt);

};
