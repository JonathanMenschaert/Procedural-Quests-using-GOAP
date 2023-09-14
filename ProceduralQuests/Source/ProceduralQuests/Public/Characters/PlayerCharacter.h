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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

	void MoveForward(const FInputActionValue& value);
	void MoveRight(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void GenerateQuest(const FInputActionValue& value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestRequested);
	UPROPERTY(BlueprintAssignable, Category = "Quests")
	FOnQuestRequested OnQuestRequested;

};
