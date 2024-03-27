// Fill out your copyright notice in the Description page of Project Settings.


#include "LocoController.h"
#include "TrainControlsHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ALocoController::ALocoController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	CameraArm->SetupAttachment(LocoBody);
	CameraArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CameraArm->SetRelativeRotation(FRotator(0.0f, -20.0f, 0.0f));
	CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));
	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ALocoController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && HUDref)
	{
		HUD = CreateWidget<UTrainControlsHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), HUDref);
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

// Called every frame
void ALocoController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canMove == true)
	{
		if (throttleOn == true)
		{
			if (isReversing == false)
			{
				LeftWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
				LeftWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
				RightWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
				RightWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * 5000.0f), 0.0f));
			}
			else
			{
				LeftWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
				LeftWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
				RightWheel1->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
				RightWheel2->AddTorqueInRadians(FVector(0.0f, (passedTorqueMulti * -5000.0f), 0.0f));
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
	}
}

//InputFunctions

void ALocoController::CameraDrag(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement"));
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}

}

void ALocoController::ExitTrain(const FInputActionValue& Value) 
{
	UE_LOG(LogTemp, Warning, TEXT("ExitTrain"));
}

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
			isReversing = true;
			canMove = true;
		}
		else if (passedDetent == 2) 
		{
			isReversing = false;
			canMove = true;
		}
		else if (passedDetent == 1) 
		{
			canMove = false;
		}
}