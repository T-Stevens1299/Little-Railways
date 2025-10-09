// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundAndSteamComponent.generated.h"


class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LITTLERAILWAYS_API USoundAndSteamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoundAndSteamComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void setComponentVariables(ALocoController* LocoControl, ALocoDrivers* Drivers, UNiagaraComponent* SteamGen, UAudioComponent* LocoSound1, UAudioComponent* LocoSound2);

	void playWhistle();

	void toggleStaticSteam();

	//Editable Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName floatParameter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName vectorParameter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxSmokeParticleSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxExhaustParticleSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector chuffVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector exhaustVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* whistleType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void SoundCalculations();
	bool wheelDegreeFinder(float curWheelRot);

	class ALocoController* locoRef;
	class ALocoDrivers* driversRef;
	class UNiagaraComponent* steamGenRef;

	UAudioComponent* LocoChuff1;
	UAudioComponent* LocoChuff2;

	int curPistonStroke;

	bool triggerSoundCalculations = false;
};