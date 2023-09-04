// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldStateModifier.generated.h"

/**
 * 
 */

class UBlackboardComponent;

UCLASS(ABSTRACT)
class PROCEDURALQUESTS_API UWorldStateModifier : public UObject
{
	GENERATED_BODY()
	
protected:

	virtual bool HasState(const UBlackboardComponent* blackboard) const;
	virtual bool ChangeState(UBlackboardComponent* blackboard) const;
};
