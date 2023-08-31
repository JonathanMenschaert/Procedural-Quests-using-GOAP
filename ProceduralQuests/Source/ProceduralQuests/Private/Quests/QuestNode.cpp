// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestNode.h"

void UQuestNode::SetNodeAction(TSubclassOf<UQuestAction*> action)
{
	Action = action;
}

void UQuestNode::AddConnectedNode(UQuestNode* node)
{
	Connections.Add(node);
}

TSubclassOf<UQuestAction*> UQuestNode::GetNodeAction() const
{
	return Action;
}

TArray<UQuestNode*> UQuestNode::GetConnectedNodes() const
{
	return Connections;
}
