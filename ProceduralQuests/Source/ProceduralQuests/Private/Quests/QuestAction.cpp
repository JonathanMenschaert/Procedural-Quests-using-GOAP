// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestAction.h"
#include "Quests/WorldStateModifier.h"

int UQuestAction::GetCost() const
{
	return Cost;
}

bool UQuestAction::Execute()
{
	return false;
}

const TArray<TSubclassOf<UWorldStateModifier>>& UQuestAction::GetEffects() const
{
	return Effects;
}

const TArray<TSubclassOf<UWorldStateModifier>>& UQuestAction::GetPreconditions() const
{
	return Preconditions;
}

bool UQuestAction::IsValid() const
{
	return false;
}
