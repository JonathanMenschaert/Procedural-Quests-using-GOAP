// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestGoal.h"

const TMap<FString, bool>& UQuestGoal::GetConditions() const
{
	return Conditions;
}
