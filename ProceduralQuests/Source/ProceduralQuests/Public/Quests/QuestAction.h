// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "QuestAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UQuestAction : public UObject
{
	GENERATED_BODY()

public:
	virtual int GetCost() const;
	virtual bool Execute();
	virtual const TMap<FString, bool>& GetEffects() const;
	virtual const TMap<FString, bool>& GetPreconditions() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	TMap<FString, bool> Effects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	TMap<FString, bool> Preconditions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	int Cost;
	
};
