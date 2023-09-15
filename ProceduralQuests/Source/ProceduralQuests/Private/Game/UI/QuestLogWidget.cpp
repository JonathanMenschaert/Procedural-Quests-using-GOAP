// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/QuestLogWidget.h"
#include "Quests/QuestGoal.h"

UQuestLogWidget::UQuestLogWidget(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
	bIsFocusable = true;
}


void UQuestLogWidget::OpenQuestLog(const TArray<TSubclassOf<UQuestGoal>>& quests, TSubclassOf<UQuestGoal> currentQuest)
{
	Quests = quests;
	CurrentQuest = currentQuest;
	OnQuestLogOpened.Broadcast();
}

TSubclassOf<UQuestGoal> UQuestLogWidget::GetSelectedQuest() const
{
	return CurrentQuest;
}

UQuestGoal* UQuestLogWidget::GetCurrentQuest() const
{
	return Cast<UQuestGoal>(CurrentQuest->GetDefaultObject());
}

UQuestGoal* UQuestLogWidget::SetSelectedQuest(int index)
{
	if (index <= Quests.Num() - 1)
	{
		CurrentQuest = Quests[index];
		return Cast<UQuestGoal>(Quests[index]->GetDefaultObject());
	}
	return nullptr;
}

UQuestGoal* UQuestLogWidget::GetQuestByIndex(int index)
{
	if (index <= Quests.Num() - 1)
	{
		return Cast<UQuestGoal>(Quests[index]->GetDefaultObject());
	}
	return nullptr;
}

int UQuestLogWidget::GetQuestLogSize() const
{
	return Quests.Num() - 1;
}
