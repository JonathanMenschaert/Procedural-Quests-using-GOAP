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
class UWorldStateModifier;

UCLASS(Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UQuestAction : public UObject
{
	GENERATED_BODY()

public:
	virtual int GetCost() const;
	virtual bool Execute();
	virtual const TArray<TSubclassOf<UWorldStateModifier>>& GetEffects() const;
	virtual const TArray<TSubclassOf<UWorldStateModifier>>& GetPreconditions() const;
	virtual bool IsValid() const;
	virtual TArray<FString> GetObjectives() const;

protected:

	UPROPERTY(EditAnywhere, Category = "General Settings")
	TArray<TSubclassOf<UWorldStateModifier>> Effects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	TArray<TSubclassOf<UWorldStateModifier>> Preconditions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "General Settings")
	int Cost;
	
};
