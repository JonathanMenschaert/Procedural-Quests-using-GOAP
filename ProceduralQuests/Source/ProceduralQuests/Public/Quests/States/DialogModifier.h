// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quests/WorldStateModifier.h"
#include "Quests/Dialog.h"
#include "DialogModifier.generated.h"
/**
 * 
 */
UCLASS()
class PROCEDURALQUESTS_API UDialogModifier : public UWorldStateModifier
{
	GENERATED_BODY()
public:
	
	virtual bool ChangeState(UBlackboardComponent* blackboard) const override;
	virtual bool HasState(const UBlackboardComponent* blackboard) const override;
	virtual bool Compare(UWorldStateModifier* state) override;
	virtual FString GetObjective() const override;

protected:


	UPROPERTY(EditAnywhere, Category = "Dialog")
	FString NpcName;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	FString QuestName;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	FDialog Dialog;
	
};
