// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestAction.h"

int UQuestAction::GetCost() const
{
	return Cost;
}

bool UQuestAction::Execute()
{
	return false;
}

const TMap<FString, bool>& UQuestAction::GetEffects() const
{
	return Effects;
}

const TMap<FString, bool>& UQuestAction::GetPreconditions() const
{
	return Preconditions;
}
