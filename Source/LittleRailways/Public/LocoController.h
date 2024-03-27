// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LittleRailways/LocomotiveParent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LittleRailways/BPI_Braking.h"
#include "Blueprint/UserWidget.h"
#include "LocoController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class LITTLERAILWAYS_API ALocoController : public APawn, public IBPI_Braking
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALocoController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CameraDrag(const FInputActionValue& Value);

	void ExitTrain(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	//Loco Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LocoBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWheel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* BrakeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* RegulatorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ReverserMesh;

	//Variables

	bool canMove;
	bool throttleOn;
	bool isReversing;
	int passedTorqueMulti;
	float speed;

public:
	//Functions
	UFUNCTION(BlueprintCallable, Category = "Loco")
	void ApplyTorque(int passedTorqueMultiplier);

	void ApplyBrakes(int passedBrakeVal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControlsRef")
	void Brake(int passedForce); void Brake_Implementation(int passedForce) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControlsRef")
	void Regulator(int passedTorque); void Regulator_Implementation(int passedTorque) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControlsRef")
	void SetReverser(int passedDetent); void SetReverser_Implementation(int passedDetent) override;

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* TrainControlsMappingContext;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* CameraDragAction;

	/** Exit Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* ExitAction;

	/** HUD Widget */
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> HUDref;

	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class UTrainControlsHUD* HUD;
};