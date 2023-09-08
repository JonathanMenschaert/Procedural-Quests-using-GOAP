// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quests/WorldStateModifier.h"
#include "InventoryModifier.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALQUESTS_API UInventoryModifier : public UWorldStateModifier
{
	GENERATED_BODY()

public:
	virtual bool HasState(const UBlackboardComponent* blackboard) const;
	virtual bool ChangeState(UBlackboardComponent* blackboard) const;	
	virtual bool Compare(UWorldStateModifier* state);

protected:

	UPROPERTY(EditAnywhere, Category = "Item")
	FString Item;

	UPROPERTY(EditAnywhere, Category = "Item")
	int Amount;
};
