// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens


#include "LocoController.h"
#include "TrainControlsHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LittleRailways/Reverser.h"
#include "LittleRailways/Regulator.h"
#include "LittleRailways/BrakeLever.h"
#include "GameFramework/Controller.h"
#include <Kismet/GameplayStatics.h>
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

	LeftWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentA"));
	LeftWheel1->SetupAttachment(LocoBody);

	LeftWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentB"));
	LeftWheel2->SetupAttachment(LocoBody);

	RightWheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentC"));
	RightWheel1->SetupAttachment(LocoBody);

	RightWheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComponentD"));
	RightWheel2->SetupAttachment(LocoBody);

	BrakeMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("BrakeComponent"));
	BrakeMesh->SetupAttachment(LocoBody);

	RegulatorMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("RegComponent"));
	RegulatorMesh->SetupAttachment(LocoBody);

	ReverserMesh = CreateDefaultSubobject<UChildActorComponent>(TEXT("ReverserComponent"));
	ReverserMesh->SetupAttachment(LocoBody);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
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

	PC->bShowMouseCursor = true;

	if (IsLocallyControlled() && HUDref)
	{
		HUD = CreateWidget<UTrainControlsHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), HUDref);
		HUD->SetTrainPtr(this);
		HUD->AddToViewport();
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TrainControlsMappingContext, 0);
		}
	}

}

void ALocoController::SetComponents()
{
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
}

// Called every frame
void ALocoController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canMove)
	{
		if (throttleOn)
		{
			if (!isReversing)
			{
				LeftWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * TractiveTorque), 0.0f));
				RightWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * TractiveTorque), 0.0f));
			}
			else
			{
				LeftWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -TractiveTorque), 0.0f));
				RightWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -TractiveTorque), 0.0f));
			}
		}
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
	UE_LOG(LogTemp, Warning, TEXT("ExitTrain"));
	PC->bShowMouseCursor = false;
}

void ALocoController::ZoomCamera(const FInputActionValue& Value) 
{
	const float newTargetArmLength = CameraArm->TargetArmLength + (Value.Get<float>() * ZoomStep);

	CameraArm->TargetArmLength = FMath::Clamp(newTargetArmLength, MinZoomLength, MaxZoomLength);
}
//End Of Input Functions


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
	float brakeVal = passedBrakeVal;

	LeftWheel1->SetAngularDamping(brakeVal);
	LeftWheel2->SetAngularDamping(brakeVal);
	RightWheel1->SetAngularDamping(brakeVal);
	RightWheel2->SetAngularDamping(brakeVal);
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
}

void ALocoController::setReverserStage(int passedDetent)
{
	ReverserComponent->setReverser(passedDetent);
}

void ALocoController::setBrakeStage(int passedDetent)
{
	BrakeLeverComponent->engageBrakeStage(passedDetent);
}