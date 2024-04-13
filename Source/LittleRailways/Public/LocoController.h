// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

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

class AReverser;
class ARegulator;
class ABrakeLever;
class ALocomotiveTender;

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

	void ZoomCamera(const FInputActionValue& Value);

	void DragTrigger(const FInputActionValue& Value);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocoParts", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* TenderMesh;

	/** Lever Components */
	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	AReverser* ReverserComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ARegulator* RegulatorComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ABrakeLever* BrakeLeverComponent;

	UPROPERTY(BlueprintReadOnly, Category = "LocoParts")
	ALocomotiveTender* TrainTenderComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawn")
	TSubclassOf<ACharacter> CharacterToSpawn;

	//Variables
	//Fuel variables
	float curFuelLevel = 0;

	bool fireActive = false;

	bool isMoving;

	//Movement Bools
	bool canMove;
	bool throttleOn;
	bool isReversing;
	bool isPressed = false;

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

	void SetComponents();

	void MoveCam();

	void SpawnCharacter();

	void setRegStage(int passedDetent);

	void setBrakeStage(int passedDetent);

	void setReverserStage(int passedDetent);

	void FuelFire();

	void SetUILevels();

	void consumeFuelandWater();

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