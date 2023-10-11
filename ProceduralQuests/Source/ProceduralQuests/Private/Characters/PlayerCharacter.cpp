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
#include "Quests/QuestManager.h"
#include "Items/Inventory.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/UI/ObjectiveWidget.h"	
#include "Quests/DialogHandler.h"
#include "Components/SphereComponent.h"
#include "Interfaces/Interactable.h"
#include "Quests/QuestStatus.h"
#include "Quests/QuestActivatorComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	DialogHandler = CreateDefaultSubobject<UDialogHandler>(TEXT("DialogHandler"));

	CanInteract = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AQuestManager* questManager = Cast<AQuestManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AQuestManager::StaticClass()));
	if (!questManager)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Could not locate QuestManager!");
		return;
	}

	UQuestStatus* questStatus = questManager->FindComponentByClass<UQuestStatus>();
	if (questStatus)
	{
		DialogHandler->OnDialogEnded.AddDynamic(questStatus, &UQuestStatus::UpdateQuestStatus);
	}

	UQuestActivator* questActivator = questManager->FindComponentByClass<UQuestActivator>();
	if (questActivator)
	{
		DialogHandler->OnDialogEnded.AddDynamic(questActivator, &UQuestActivator::UpdateQuestStatus);
	}

	UQuestPlanner* planner = questManager->FindComponentByClass<UQuestPlanner>();
	if (planner)
	{
		OnQuestLogOpened.AddDynamic(planner, &UQuestPlanner::OpenQuestLog);
		OnQuestRequested.AddDynamic(planner, &UQuestPlanner::SetQuestsToUpdate);

		Inventory->OnInventoryChanged.AddDynamic(planner, &UQuestPlanner::SetQuestsToUpdate);
		
		UBlackboardComponent* blackBoard = questManager->GetBlackboard();
		if (blackBoard && Inventory)
		{

			blackBoard->SetValueAsObject(FName("Inventory"), Inventory);
		}
	}

	WorldStates = questManager->GetBlackboard();
	if (!WorldStates)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Could not find blackboard!");
	}

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
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

void APlayerCharacter::Interact(const FInputActionValue& value)
{
	if (Interactables.Num() > 0 && !DialogHandler->HasDialogActive())
	{
		FDialog dialog{};
		IInteractable* interactable = Interactables[0];
		UObject* interactableObj = Cast<UObject>(interactable);
		FString questName = WorldStates->GetValueAsString("CurrentQuest");
		interactable->Execute_Interact(interactableObj, questName, dialog);
		DialogHandler->InitiateDialog(dialog, questName);
	}
}

void APlayerCharacter::GenerateQuest(const FInputActionValue& value)
{
	if (OnQuestRequested.IsBound())
	{
		OnQuestRequested.Broadcast();
	}
}

void APlayerCharacter::ToggleQuestLog(const FInputActionValue& value)
{
	if (OnQuestLogOpened.IsBound())
	{
		OnQuestLogOpened.Broadcast();
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	IInteractable* interactableActor = Cast<IInteractable>(otherActor);
	if (interactableActor)
	{
		Interactables.AddUnique(interactableActor);
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex)
{
	IInteractable* interactableActor = Cast<IInteractable>(otherActor);
	if (interactableActor)
	{
		Interactables.Remove(interactableActor);
	}
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
	pEnhancedInput->BindAction(InputConfig->InputMoveForward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
	pEnhancedInput->BindAction(InputConfig->InputMoveRight, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
	pEnhancedInput->BindAction(InputConfig->InputRequestQuest, ETriggerEvent::Started, this, &APlayerCharacter::GenerateQuest);
	pEnhancedInput->BindAction(InputConfig->InputOpenQuestLog, ETriggerEvent::Started, this, &APlayerCharacter::ToggleQuestLog);
	pEnhancedInput->BindAction(InputConfig->InputInteract, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
}

