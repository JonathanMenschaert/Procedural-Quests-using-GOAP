// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestGoal.h"
#include "Quests/WorldStateModifier.h"

const TArray<UWorldStateModifier*>& UQuestGoal::GetConditions() const
{
	return Conditions;
}
