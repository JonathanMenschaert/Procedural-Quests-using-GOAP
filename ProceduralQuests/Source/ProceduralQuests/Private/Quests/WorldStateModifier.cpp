// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/WorldStateModifier.h"

bool UWorldStateModifier::HasState(const UBlackboardComponent* blackboard) const
{
	return false;
}

bool UWorldStateModifier::ChangeState(UBlackboardComponent* blackboard) const
{
	return false;
}

bool UWorldStateModifier::Compare(UWorldStateModifier* state)
{
	return false;
}

FString UWorldStateModifier::GetObjective() const
{
	return FString("Create a subclass to display custom objectives!");
}
