// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestGoal.h"
#include "Quests/WorldStateModifier.h"

const TArray<TSubclassOf<UWorldStateModifier>>& UQuestGoal::GetConditions() const
{
	return Conditions;
}

void UQuestGoal::SetCompleted(bool complete)
{
	IsQuestCompleted = complete;
}

bool UQuestGoal::IsCompleted() const
{
	return IsQuestCompleted;
}

const FString& UQuestGoal::GetQuestName() const
{
	return QuestName;
}
