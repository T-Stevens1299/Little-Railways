// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "LocoController.h"
#include "TrainControlsHUD.h"
#include "TimerManager.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LittleRailways/Reverser.h"
#include "LittleRailways/Regulator.h"
#include "LittleRailways/BrakeLever.h"
#include "LocomotiveTender.h"
#include "LocoDrivers.h"
#include "StationClass.h"
#include "GameFramework/Controller.h"
#include <Kismet/GameplayStatics.h>
#include "LittleRailways/LittleRailwaysCharacter.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ALocoController::ALocoController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	LocoBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	LocoBody->SetupAttachment(GetRootComponent());

	DriverSet1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Driver1Component"));
	DriverSet1->SetupAttachment(LocoBody);

	DriverSet2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Driver2Component"));
	DriverSet2->SetupAttachment(LocoBody);

	Coupling1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coupling1Component"));
	Coupling1->SetupAttachment(LocoBody);

	Coupling2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coupling2Component"));
	Coupling2->SetupAttachment(LocoBody);

	BrakeMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("BrakeComponent"));
	BrakeMesh->SetupAttachment(LocoBody);

	RegulatorMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("RegComponent"));
	RegulatorMesh->SetupAttachment(LocoBody);

	ReverserMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("ReverserComponent"));
	ReverserMesh->SetupAttachment(LocoBody);

	TenderMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("TenderComponent"));
	TenderMesh->SetupAttachment(LocoBody);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(LocoBody);
	CameraArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Position the camera
	CameraArm->TargetArmLength = 400.0f;	
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ALocoController::BeginPlay()
{
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	SetComponents();

	HUD = CreateWidget<UTrainControlsHUD>(PC, HUDref);
	HUD->SetTrainPtr(this);

	SetUILevels();

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ALocoController::consumeFuelandWater, 10.0f, true, 10.0f);
}

//Sets up the references for the child actor components
void ALocoController::SetComponents()
{
	DriverSet1Component = Cast<ALocoDrivers>(DriverSet1->GetChildActor());
	if (DriverSet1Component)
	{
		DriverSet1Component->SetTrainPtr(this);
	}

	DriverSet2Component = Cast<ALocoDrivers>(DriverSet2->GetChildActor());
	if (DriverSet2Component)
	{
		DriverSet2Component->SetTrainPtr(this);
	}

	ReverserComponent = Cast<AReverser>(ReverserMesh->GetChildActor());
	if (ReverserComponent)
	{
		ReverserComponent->SetTrainPtr(this);
	}

	RegulatorComponent = Cast<ARegulator>(RegulatorMesh->GetChildActor());
	if (RegulatorComponent)
	{
		RegulatorComponent->SetTrainPtr(this);
	}

	BrakeLeverComponent = Cast<ABrakeLever>(BrakeMesh->GetChildActor());
	if (BrakeLeverComponent)
	{
		BrakeLeverComponent->SetTrainPtr(this);
	}

	TrainTenderComponent = Cast<ALocomotiveTender>(TenderMesh->GetChildActor());
	if (TrainTenderComponent)
	{
		TrainTenderComponent->SetTrainPtr(this);
	}
}

void ALocoController::Possessed() 
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TrainControlsMappingContext, 0);
		}
	}

	if (IsLocallyControlled() && HUDref)
	{
		PC->bShowMouseCursor = true;
		HUD->AddToViewport();
	}
}

// Called every frame
void ALocoController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (curFuelLevel == 0)
	{
		fireActive = false;
	}

	if (canMove && fireActive && TrainTenderComponent->curWaterAmount > 0)
	{
		if (throttleOn)
		{
			if (!isReversing)
			{
				if (DriverSet1Component)
				{
					DriverSet1Component->ApplyTorque(passedTorqueMulti);
				}
				if (DriverSet2Component)
				{
					DriverSet2Component->ApplyTorque(passedTorqueMulti);
				}
				ToggleMovementSteam();
			}
			else
			{
				if (DriverSet1Component)
				{
					DriverSet1Component->ApplyTorque(-passedTorqueMulti);
				}
				if (DriverSet2Component)
				{
					DriverSet2Component->ApplyTorque(-passedTorqueMulti);
				}
				ToggleMovementSteam();
			}
		}
	}
	else
	{
		ToggleStaticSteam();
	}

	speed = ((GetVelocity().Size2D() * 3600) / 100000);

	HUD->SpeedCalculator(speed);
}

// Called to bind functionality to input
void ALocoController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(CameraDragAction, ETriggerEvent::Triggered, this, &ALocoController::CameraDrag);

		EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Triggered, this, &ALocoController::ExitTrain);

		EnhancedInputComponent->BindAction(CameraZoom, ETriggerEvent::Triggered, this, &ALocoController::ZoomCamera);

		EnhancedInputComponent->BindAction(DragTriggerAction, ETriggerEvent::Triggered, this, &ALocoController::DragTrigger);

		EnhancedInputComponent->BindAction(HideHUD, ETriggerEvent::Triggered, this, &ALocoController::ToggleHUD);
	}
}

//Input Functions
void ALocoController::CameraDrag(const FInputActionValue& Value)
{
	if (isPressed == true)
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void ALocoController::DragTrigger(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Triggered"));
	if (isPressed)
	{
		isPressed = false;
		PC->bShowMouseCursor = true;
	}
	else
	{
		isPressed = true;
		PC->bShowMouseCursor = false;
	}
}

void ALocoController::ExitTrain(const FInputActionValue& Value) 
{
	PC->bShowMouseCursor = false;
	UE_LOG(LogTemp, Warning, TEXT("SpawnCharacter"));
	HUD->RemoveFromParent();
	SpawnCharacter();
}

void ALocoController::ZoomCamera(const FInputActionValue& Value) 
{
	const float newTargetArmLength = CameraArm->TargetArmLength + (Value.Get<float>() * ZoomStep);

	CameraArm->TargetArmLength = FMath::Clamp(newTargetArmLength, MinZoomLength, MaxZoomLength);
}

void ALocoController::ToggleHUD(const FInputActionValue& Value)
{
	if (hudVisible)
	{
		HUD->SetVisibility(ESlateVisibility(false));
		hudVisible = false;
	}
	else
	{
		HUD->SetVisibility(ESlateVisibility(true));
		hudVisible = true;
	}
}
//End Of Input Functions

void ALocoController::SpawnCharacter()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* SpawnedCharacter = GetWorld()->SpawnActor<APawn>(CharacterToSpawn, (GetActorLocation() + FVector(200.0f, 200.0f, 0.0f)), GetActorRotation(), SpawnParams);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(TrainControlsMappingContext);
	}

	PC->Possess(SpawnedCharacter);
	Cast<ALittleRailwaysCharacter>(SpawnedCharacter)->Possessed();
}

//Force application functions
void ALocoController::ApplyTorque(int passedTorqueMultiplier)
{
	passedTorqueMulti = passedTorqueMultiplier;
	if (passedTorqueMulti != 0)
	{
		throttleOn = true;

	}
}

void ALocoController::ApplyBrakes(int passedBrakeVal)
{
	DriverSet1Component->ApplyBreaks(passedBrakeVal);
	if (DriverSet2Component)
	{
		DriverSet2Component->ApplyBreaks(passedBrakeVal);
	}
}


//Interface functions
void ALocoController::Brake_Implementation(int passedForce)
{
	ApplyBrakes(passedForce);
}

void ALocoController::Regulator_Implementation(int passedTorque)
{
	throttleOn = false;
	ApplyTorque(passedTorque);
}

void ALocoController::SetReverser_Implementation(int passedDetent)
{
		if (passedDetent == 0)
		{
			canMove = true;
			isReversing = true;
		}
		else if (passedDetent == 2) 
		{
			canMove = true;
			isReversing = false;
		}
		else if (passedDetent == 1) 
		{
			canMove = false;
		}
}

//Lever Movement
void ALocoController::setRegStage(int passedDetent)
{
	RegulatorComponent->engageRegulator(passedDetent);
	if (passedDetent == 0)
	{
		ToggleStaticSteam();
	}
}

void ALocoController::setReverserStage(int passedDetent)
{
	ReverserComponent->setReverser(passedDetent);
}

void ALocoController::setBrakeStage(int passedDetent)
{
	BrakeLeverComponent->engageBrakeStage(passedDetent);
}

//Fuel Functions
void ALocoController::SetUILevels()
{
	HUD->totalCoalLevel = TrainTenderComponent->fuelCapacity;
	HUD->totalWaterLevel = TrainTenderComponent->waterCapacity;

	HUD->UpdateFireLevel(0.0f);
	HUD->UpdateWaterLevel(TrainTenderComponent->waterCapacity);
	HUD->UpdateCoalLevel(TrainTenderComponent->fuelCapacity);
}

void ALocoController::togglePassengerButtons(bool isUP, AStationClass* stationRef)
{
	isUp = isUP;
	StationRef = stationRef;
	HUD->ToggleButtons();
}

void ALocoController::FuelFire()
{
	if (!(TrainTenderComponent->curFuelAmount <= 0))
	{
		if (curFuelLevel < 100)
		{
			if (curFuelLevel + 25.0f <= 100)
			{
				curFuelLevel = curFuelLevel + 25.0f;
			}
			else
			{
				curFuelLevel = 100;
			}
		}

		fireActive = true;
		TrainTenderComponent->consumeFuel(5.0f);
		HUD->UpdateFireLevel(curFuelLevel);
		HUD->UpdateCoalLevel(TrainTenderComponent->curFuelAmount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoFuel"));
	}
}

void ALocoController::consumeFuelandWater()
{
	if (fireActive)
	{
		TrainTenderComponent->consumeWater(1.0f);
		if (curFuelLevel - 1.0f == 0)
		{
			curFuelLevel = 0;
		}
		else
		{
			curFuelLevel = curFuelLevel - 1.0f;
		}
		HUD->UpdateWaterLevel(TrainTenderComponent->curWaterAmount);
		HUD->UpdateFireLevel(curFuelLevel);
	}
}

void ALocoController::AddFuel_Implementation(float passedFuelToAdd, bool isWater)
{
	if (isWater)
	{
		TrainTenderComponent->increaseWater(passedFuelToAdd);
	}
	else
	{
		TrainTenderComponent->increaseFuel(passedFuelToAdd);
	}
}