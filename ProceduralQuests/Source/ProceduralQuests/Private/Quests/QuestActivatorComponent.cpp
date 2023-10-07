// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestActivatorComponent.h"
#include "Quests/QuestGoal.h"
#include "Quests/QuestPlanner.h"

// Sets default values for this component's properties
UQuestActivator::UQuestActivator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestActivator::BeginPlay()
{
	Super::BeginPlay();
	QuestPlanner = GetOwner()->GetComponentByClass<UQuestPlanner>();
	for (TSubclassOf<UQuestGoal>& questClass : QuestClasses)
	{		
		Quests.Add(NewObject<UQuestGoal>(this, questClass));	
	}

	BuildRequrementMap();
	ActivateQuestRequirement(FString("Start"));
}

void UQuestActivator::ActivateQuestRequirement(FString questName)
{
	FRequirements* requiredQuests = RequirementMap.Find(questName);
	if (!requiredQuests)
	{
		
		return;
	}
	for (UQuestGoal* requiredQuest : requiredQuests->AttachedQuests)
	{
		requiredQuest->RemoveRequirement(questName);
		
		if (requiredQuest->RequirementsLeft() <= 0)
		{
			
			requiredQuest->OnQuestCompleted.BindUObject(this, &UQuestActivator::ActivateQuestRequirement);
			QuestPlanner->AddQuest(requiredQuest);
		}
	}
	QuestPlanner->UpdateQuests();
}

void UQuestActivator::BuildRequrementMap()
{
	for (UQuestGoal* quest : Quests)
	{
		if (!quest)
		{			
			continue;
		}
		for (const FString& questName : quest->GetQuestRequirements())		
		{
			
			FRequirements* requirements = RequirementMap.Find(questName);
			if (requirements)
			{
				requirements->AttachedQuests.Add(quest);
			}
			else
			{
				FRequirements req = FRequirements{};
				req.AttachedQuests.Add(quest);
				RequirementMap.Add(questName, req);
			}
		}
	}
}


// Called every frame
void UQuestActivator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

