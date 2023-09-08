// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestNode.h"
#include "Quests/QuestAction.h"

void UQuestNode::SetNodeAction(UQuestAction* action)
{
	Action = action;
}

void UQuestNode::AddConnectedNode(UQuestNode* node)
{
	Connections.Add(node);
}

UQuestAction* UQuestNode::GetNodeAction() const
{
	return Action;
}

TArray<UQuestNode*> UQuestNode::GetConnectedNodes() const
{
	return Connections;
}

bool UQuestNode::HasConnectedNodes() const
{
	return Connections.Num() > 0;
}
