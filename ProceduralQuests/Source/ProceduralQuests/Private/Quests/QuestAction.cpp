// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestAction.h"
#include "Quests/WorldStateModifier.h"
#include "BehaviorTree/BlackboardComponent.h"

int UQuestAction::GetCost() const
{
	return Cost;
}

bool UQuestAction::HasResultState(UBlackboardComponent* blackboard)
{
	for (const TSubclassOf<UWorldStateModifier>& stateMod : Results)
	{
		UWorldStateModifier* state{ Cast<UWorldStateModifier>(stateMod->GetDefaultObject()) };
		if (!state->HasState(blackboard))
		{
			return false;
		}
	}
	return true;
}

void UQuestAction::ExecuteResults(UBlackboardComponent* blackboard)
{
	for (const TSubclassOf<UWorldStateModifier>& stateMod : Results)
	{
		UWorldStateModifier* state{ Cast<UWorldStateModifier>(stateMod->GetDefaultObject()) };
		state->ChangeState(blackboard);
	}
}

void UQuestAction::ExecuteEffects(UBlackboardComponent* blackboard)
{
	for (const TSubclassOf<UWorldStateModifier>& stateMod : Effects)
	{
		UWorldStateModifier* state{ Cast<UWorldStateModifier>(stateMod->GetDefaultObject()) };
		state->ChangeState(blackboard);
	}
}

void UQuestAction::RevertEffects(UBlackboardComponent* blackboard)
{

}

const TArray<TSubclassOf<UWorldStateModifier>>& UQuestAction::GetEffects() const
{
	return Effects;
}

const TArray<TSubclassOf<UWorldStateModifier>>& UQuestAction::GetResults() const
{
	return Results;
}

const TArray<TSubclassOf<UWorldStateModifier>>& UQuestAction::GetPreconditions() const
{
	return Preconditions;
}

bool UQuestAction::IsValid(const UBlackboardComponent* blackboard) const
{
	for (const TSubclassOf<UWorldStateModifier>& stateMod : Preconditions)
	{
		UWorldStateModifier* state{ Cast<UWorldStateModifier>(stateMod->GetDefaultObject()) };
		if (!state->HasState(blackboard))
		{
			return false;
		}
	}
	return true;
}

TArray<FString> UQuestAction::GetObjectives() const
{
	TArray<FString> objectives{ TArray<FString>() };
	for (const TSubclassOf<UWorldStateModifier>& stateMod : Results)
	{
		UWorldStateModifier* state{ Cast<UWorldStateModifier>(stateMod->GetDefaultObject()) };
		objectives.Emplace(state->GetObjective());
	}

	return objectives;
}
