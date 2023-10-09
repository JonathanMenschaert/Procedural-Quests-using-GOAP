// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestStatus.h"

// Sets default values for this component's properties
UQuestStatus::UQuestStatus()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestStatus::UpdateQuestStatus(FString questName, FString dialogId)
{
	QuestStates.Add(questName, dialogId);
}

const FString& UQuestStatus::GetStatus(const FString& questName)
{
	FString* status = QuestStates.Find(questName);
	if (!status)
	{
		status = QuestStates.Find("Default");
	}
	return *status;
}

void UQuestStatus::BeginPlay()
{
	Super::BeginPlay();

	QuestStates.Add("Default", "Default_0");
}
