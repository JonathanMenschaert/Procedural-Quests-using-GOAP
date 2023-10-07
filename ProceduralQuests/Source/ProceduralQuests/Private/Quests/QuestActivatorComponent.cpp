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
		UQuestGoal* test = NewObject<UQuestGoal>(this, questClass);
		if (test)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "valid");
			Quests.Add(test);
		}
		
	}

	BuildRequrementMap();
	//ActivateQuestRequirement(FString("Start"));
}

void UQuestActivator::ActivateQuestRequirement(FString questName)
{
	FRequirements* requiredQuests = RequirementMap.Find(questName);
	if (!requiredQuests)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "requirement is gone");
		return;
	}
	for (UQuestGoal* requiredQuest : requiredQuests->AttachedQuests)
	{
		requiredQuest->RemoveRequirement(questName);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Removed requirement");
		if (requiredQuest->RequirementsLeft() <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Requirement at 0");
			requiredQuest->OnQuestCompleted.BindUObject(this, &UQuestActivator::ActivateQuestRequirement);
			//QuestPlanner->AddQuest(requiredQuest);
		}
	}
	QuestPlanner->UpdateQuests();
}

void UQuestActivator::BuildRequrementMap()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(Quests.Num()));
	for (UQuestGoal* quest : Quests)
	{
		if (!quest)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "quest not found");
			continue;
		}
		if (quest->GetQuestRequirements().Num() <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "No Requirements found");
		}
		for (const FString& questName : quest->GetQuestRequirements())		
		{
			
			FRequirements* requirements = RequirementMap.Find(questName);
			if (requirements)
			{
				requirements->AttachedQuests.Add(quest);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "requirement existed");
			}
			else
			{
				FRequirements req = FRequirements{};
				req.AttachedQuests.Add(quest);
				RequirementMap.Add(questName, req);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "requirement did not exist");
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

