// Copyright Epic Games, Inc. All Rights Reserved.

#include "LittleRailwaysCharacter.h"
#include "LittleRailwaysProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Kismet/GameplayStatics.h>
#include "LocoController.h"
#include "ShopHUD.h"
#include "BPI_Interact.h"
#include "BPI_StatsIncrease.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ALittleRailwaysCharacter

ALittleRailwaysCharacter::ALittleRailwaysCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ALittleRailwaysCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	gmRef = Cast<ALittleRailwaysGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//Shop out of order until I get round to fixing data table bug
	//SHOP = CreateWidget<UShopHUD>(PC, Shopref);
	//SHOP->SetGMptr(gmRef);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void ALittleRailwaysCharacter::Possessed() 
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ALittleRailwaysCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALittleRailwaysCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALittleRailwaysCharacter::Look);

		// Train Boarding
		EnhancedInputComponent->BindAction(TrainBoardAction, ETriggerEvent::Triggered, this, &ALittleRailwaysCharacter::BoardTrain);
		
		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ALittleRailwaysCharacter::Interact);
		
		// HUD Toggling
		EnhancedInputComponent->BindAction(HudAction, ETriggerEvent::Triggered, this, &ALittleRailwaysCharacter::toggleHUD);

		EnhancedInputComponent->BindAction(ShopAction, ETriggerEvent::Triggered, this, &ALittleRailwaysCharacter::openShopMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALittleRailwaysCharacter::toggleHUD(const FInputActionValue& Value)
{
	gmRef->ToggleHUD();
}

void ALittleRailwaysCharacter::BoardTrain(const FInputActionValue& Value)
{
	if (gmRef->HUDon)
	{
		gmRef->ToggleHUD();
	}
	PerformLineTrace();
}

void ALittleRailwaysCharacter::openShopMenu(const FInputActionValue& Value)
{
	SHOP->updateMoneyXP();
	SHOP->AddToViewport();
	PC->bShowMouseCursor = true;
	PC->SetInputMode(FInputModeUIOnly());
}

void ALittleRailwaysCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
	FHitResult HitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	FVector startLoc = FirstPersonCameraComponent->GetComponentLocation();
	FVector endLoc = startLoc + (FirstPersonCameraComponent->GetForwardVector() * 250.0f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, startLoc, endLoc, ECollisionChannel::ECC_Camera, params, FCollisionResponseParams()))
	{
		IBPI_Interact* InteractInterface = Cast<IBPI_Interact>(HitResult.GetActor());
		DrawDebugLine(GetWorld(), startLoc, endLoc, HitResult.GetActor() ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
		if (InteractInterface)
		{
			InteractInterface->Execute_Interact(HitResult.GetActor());
		}
	}
}

void ALittleRailwaysCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALittleRailwaysCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALittleRailwaysCharacter::PerformLineTrace()
{
	FHitResult HitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	
	FVector startLoc = FirstPersonCameraComponent->GetComponentLocation();
	FVector endLoc = startLoc + (FirstPersonCameraComponent->GetForwardVector() * 250.0f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, startLoc, endLoc, ECollisionChannel::ECC_Camera, params, FCollisionResponseParams()))
	{
		ALocoController* foundLoco = Cast<ALocoController>(HitResult.GetActor());

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
		}

		PC->Possess(foundLoco);
		Cast<ALocoController>(foundLoco)->Possessed();

		Destroy();
	}

	/*DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, 5.0f, 0, 5.0f);*/
}

void ALittleRailwaysCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ALittleRailwaysCharacter::GetHasRifle()
{
	return bHasRifle;
}