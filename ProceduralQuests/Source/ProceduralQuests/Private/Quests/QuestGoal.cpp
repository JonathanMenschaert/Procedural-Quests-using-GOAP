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

void UQuestGoal::CompleteQuest()
{
	IsQuestCompleted = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Quest Completed!");

	//Subscribed objects will be notified the next tick to ensure all necessary calculations are done 
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UQuestGoal::NotifyQuestCompleted);
}

const FString& UQuestGoal::GetQuestName() const
{
	return QuestName;
}

void UQuestGoal::RemoveRequirement(const FString& requirement)
{
	Requirements.Remove(requirement);
}

int UQuestGoal::RequirementsLeft() const
{
	return Requirements.Num();
}

const TArray<FString>& UQuestGoal::GetQuestRequirements() const
{
	return Requirements;
}

void UQuestGoal::NotifyQuestCompleted()
{
	OnQuestCompleted.ExecuteIfBound(QuestName);
}
