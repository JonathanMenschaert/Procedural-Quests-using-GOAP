// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestGoal.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UQuestGoal : public UObject
{
	GENERATED_BODY()

public:

	virtual const TMap<FString, bool>& GetConditions() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	FString QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	TMap<FString, bool> Conditions;

	
};
