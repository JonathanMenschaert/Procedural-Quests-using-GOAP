// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Private/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Input/InputConfig.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	if (Controller)
	{
		const FVector2D moveVal = value.Get<FVector2D>();
		const FRotator moveRotation{ 0, Controller->GetControlRotation().Yaw, 0 };

		if (moveVal.Y != 0.f)
		{
			const FVector dir = moveRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(dir, moveVal.Y);
		}

		if (moveVal.X != 0.f)
		{
			const FVector dir = moveRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(dir, moveVal.X);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{

	if (Controller)
	{
		const FVector2D lookVal = value.Get<FVector2D>();

		if (lookVal.X != 0.f)
		{
			AddControllerYawInput(lookVal.X);
		}

		if (lookVal.Y != 0.f)
		{
			AddControllerPitchInput(lookVal.Y);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* pPlayerController = Cast<APlayerController>(GetController());	

	UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pPlayerController->GetLocalPlayer());
	inputSystem->ClearAllMappings();
	inputSystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* pEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	pEnhancedInput->BindAction(InputConfig->InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	pEnhancedInput->BindAction(InputConfig->InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
}

