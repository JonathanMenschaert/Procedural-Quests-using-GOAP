// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfig.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALQUESTS_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputAction* GetMoveForwardInput();
	UInputAction* GetMoveRightInput();
	UInputAction* GetLookInput();
	UInputAction* GetQuestRequestInput();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	UInputAction* InputRequestQuest;

	
};
