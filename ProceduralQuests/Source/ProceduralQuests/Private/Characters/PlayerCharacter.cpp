// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Input/InputConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/QuestGameMode.h"
#include "Quests/QuestPlanner.h"
#include "Items/Inventory.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AQuestGameMode* questGameMode = Cast<AQuestGameMode>(GetWorld()->GetAuthGameMode());
	UQuestPlanner* planner = questGameMode->FindComponentByClass<UQuestPlanner>();
	if (planner)
	{
		OnQuestRequested.AddDynamic(planner, &UQuestPlanner::GenerateQuest);

		UBlackboardComponent* blackBoard = planner->GetBlackboard();
		if (blackBoard && Inventory)
		{

			blackBoard->SetValueAsObject(FName("Inventory"), Inventory);
		}
	}
	
}

void APlayerCharacter::MoveForward(const FInputActionValue& value)
{
	if (Controller)
	{
		const float moveVal = value.Get<float>();
		if (moveVal == 0.f)
		{
			return;
		}
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, moveVal);
	}
}

void APlayerCharacter::MoveRight(const FInputActionValue& value)
{
	if (Controller)
	{
		const float moveVal = value.Get<float>();
		if (moveVal == 0.f)
		{
			return;
		}
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, moveVal);
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

void APlayerCharacter::GenerateQuest(const FInputActionValue& value)
{
	if (OnQuestRequested.IsBound())
	{
		OnQuestRequested.Broadcast();
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
	pEnhancedInput->BindAction(InputConfig->GetLookInput(), ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	pEnhancedInput->BindAction(InputConfig->GetMoveForwardInput(), ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
	pEnhancedInput->BindAction(InputConfig->GetMoveRightInput(), ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
	pEnhancedInput->BindAction(InputConfig->GetQuestRequestInput(), ETriggerEvent::Started, this, &APlayerCharacter::GenerateQuest);
}

