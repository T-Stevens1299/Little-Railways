// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LittleRailways/LocomotiveParent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LittleRailways/BPI_Braking.h"
#include "BPI_Fueling.h"
#include "Blueprint/UserWidget.h"
#include "LocoController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class AReverser;
class ARegulator;
class ABrakeLever;
class ALocomotiveTender;
class AStationClass;
class ALocoDrivers;

UCLASS()
class LITTLERAILWAYS_API ALocoController : public APawn, public IBPI_Braking, public IBPI_Fueling
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

	void ZoomCamera(const FInputActionValue& Value);

	void DragTrigger(const FInputActionValue& Value);

	void ToggleHUD(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	//Loco Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LocoBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* BrakeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* RegulatorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ReverserMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* TenderMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* DriverSet1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* DriverSet2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Coupling1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Coupling2;

	/** Lever Components */
	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	AReverser* ReverserComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ARegulator* RegulatorComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ABrakeLever* BrakeLeverComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ALocomotiveTender* TrainTenderComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ALocoDrivers* DriverSet1Component;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ALocoDrivers* DriverSet2Component;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawn")
	TSubclassOf<ACharacter> CharacterToSpawn;

	//Variables

	//Station Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	AStationClass* StationRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassengerData")
	bool isUp;
	//Fuel variables
	float curFuelLevel = 0;

	bool fireActive = false;

	bool isMoving;

	//Movement Bools
	bool canMove;
	bool throttleOn;
	bool isReversing;
	bool isPressed = false;
	bool hudVisible = true;

	//Movement Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float TractiveTorque;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxSpeedKph;

	int passedTorqueMulti;

	float speed;

	FVector2D PreviousMouseLocation;

public:
	//Functions
	UFUNCTION(BlueprintCallable, Category = "Loco")
	void ApplyTorque(int passedTorqueMultiplier);

	UFUNCTION(BlueprintCallable, Category = "Loco")
	void Possessed();

	void ApplyBrakes(int passedBrakeVal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControlsRef")
	void Brake(int passedForce); void Brake_Implementation(int passedForce) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControlsRef")
	void Regulator(int passedTorque); void Regulator_Implementation(int passedTorque) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControlsRef")
	void SetReverser(int passedDetent); void SetReverser_Implementation(int passedDetent) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractEventRef")
	void AddFuel(float passedFuelToAdd, bool isWater); void AddFuel_Implementation(float passedFuelToAdd, bool isWater) override;

	void SetComponents();

	void MoveCam();

	void SpawnCharacter();

	void setRegStage(int passedDetent);

	void setBrakeStage(int passedDetent);

	void setReverserStage(int passedDetent);

	void FuelFire();

	void SetUILevels();

	void consumeFuelandWater();

	void togglePassengerButtons(bool isUP, AStationClass* stationRef);

	FTimerHandle MemberTimerHandle;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return Camera; }

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* TrainControlsMappingContext;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraDragAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* DragTriggerAction;

	/** Exit Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* ExitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* HideHUD;

	/** HUD Widget */
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> HUDref;

	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class UTrainControlsHUD* HUD;

	/** Camera Zoom Properties */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinZoomLength = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxZoomLength = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultArmLength = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomStep = 10.0f;

	APlayerController* PC;

};