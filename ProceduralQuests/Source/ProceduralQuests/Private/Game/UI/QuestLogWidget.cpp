// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/QuestLogWidget.h"
#include "Quests/QuestGoal.h"

void UQuestLogWidget::OpenQuestLog(const TArray<UQuestGoal*>& quests, UQuestGoal* currentQuest)
{
	Quests = quests;
	CurrentQuest = currentQuest;
	OnQuestLogOpened.Broadcast();
}

UQuestGoal* UQuestLogWidget::GetSelectedQuest() const
{
	return CurrentQuest;
}

UQuestGoal* UQuestLogWidget::SetSelectedQuest(int index)
{
	if (index <= Quests.Num() - 1)
	{
		CurrentQuest = Quests[index];
		return Quests[index];
	}
	return nullptr;
}

UQuestGoal* UQuestLogWidget::GetQuestByIndex(int index)
{
	if (index <= Quests.Num() - 1)
	{
		return Quests[index];
	}
	return nullptr;
}

int UQuestLogWidget::GetQuestLogSize() const
{
	return Quests.Num() - 1;
}
