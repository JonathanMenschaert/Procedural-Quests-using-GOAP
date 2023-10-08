// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"


struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UObjectiveWidget;
class UInventory;
class UDialogHandler;
class USphereComponent;
class IInteractable;
UCLASS()
class PROCEDURALQUESTS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	class UInputConfig* InputConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UDialogHandler* DialogHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	USphereComponent* InteractionSphere;

	UFUNCTION()
	void MoveForward(const FInputActionValue& value);

	UFUNCTION()
	void MoveRight(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);

	UFUNCTION()
	void Interact(const FInputActionValue& value);

	void GenerateQuest(const FInputActionValue& value);
	void ToggleQuestLog(const FInputActionValue& value);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestRequested);
	UPROPERTY(BlueprintAssignable, Category = "Quests")
	FOnQuestRequested OnQuestRequested;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestLogOpened);
	UPROPERTY(BlueprintAssignable, Category = "Quests")
	FOnQuestLogOpened OnQuestLogOpened;


private:
	UPROPERTY()
	TArray<IInteractable*> Interactables;

	bool CanInteract;

};
