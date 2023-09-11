// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldStateModifier.generated.h"

/**
 * 
 */

class UBlackboardComponent;

UCLASS(ABSTRACT, Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UWorldStateModifier : public UObject
{
	GENERATED_BODY()
	
public:

	virtual bool HasState(const UBlackboardComponent* blackboard) const;
	virtual bool ChangeState(UBlackboardComponent* blackboard) const;
	virtual bool Compare(UWorldStateModifier* state);
	virtual FString GetObjective() const;
};
