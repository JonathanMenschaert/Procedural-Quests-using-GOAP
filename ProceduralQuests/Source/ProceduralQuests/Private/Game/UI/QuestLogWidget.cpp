// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/QuestLogWidget.h"
#include "Quests/QuestGoal.h"

UQuestLogWidget::UQuestLogWidget(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
	bIsFocusable = true;
}

void UQuestLogWidget::OpenQuestLog(const TArray<UQuestGoal*> quests)
{
	Quests = quests;
	OnQuestLogOpened.Broadcast();
}
