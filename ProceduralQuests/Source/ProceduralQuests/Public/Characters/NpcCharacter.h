// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "../Quests/Dialog.h"
#include "../Interfaces/Interactable.h"
#include "NpcCharacter.generated.h"
/**
 * 
 */
UCLASS()
class PROCEDURALQUESTS_API ANpcCharacter : public ABaseCharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Dialog")
	FDialog DefaultDialog;

	UPROPERTY()
	TMap<FString, FDialog> Dialogs;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(const FString& request, FDialog& outDialog);

	void SetNewDialog(const FString& quest, const FDialog& dialog);
	
};
