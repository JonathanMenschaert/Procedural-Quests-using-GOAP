// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestNode.generated.h"

/**
 * 
 */

class UQuestAction;

UCLASS()
class PROCEDURALQUESTS_API UQuestNode : public UObject
{
	GENERATED_BODY()

public:

	void SetNodeAction(TSubclassOf<UQuestAction*> action);
	void AddConnectedNode(UQuestNode* node);
	
	TSubclassOf<UQuestAction*> GetNodeAction() const;
	TArray<UQuestNode*> GetConnectedNodes() const;
	
private:

	UPROPERTY()
	TSubclassOf<UQuestAction*> Action;

	UPROPERTY()
	TArray<UQuestNode*> Connections;

};
