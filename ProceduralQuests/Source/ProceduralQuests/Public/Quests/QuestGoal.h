// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestGoal.generated.h"

/**
 * 
 */
class UWorldStateModifier;

UCLASS(Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UQuestGoal : public UObject
{
	GENERATED_BODY()

public:

	virtual const TArray<UWorldStateModifier*>& GetConditions() const;

protected:

	UPROPERTY(EditAnywhere, Category = "General Settings")
	FString QuestName;

	UPROPERTY(EditAnywhere, Category = "General Settings")
	TArray<UWorldStateModifier*> Conditions;

	
};
