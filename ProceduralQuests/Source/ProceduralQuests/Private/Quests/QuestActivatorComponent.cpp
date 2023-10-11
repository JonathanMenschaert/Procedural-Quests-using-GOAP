#include "Quests/QuestActivatorComponent.h"
#include "Quests/QuestGoal.h"
#include "Quests/QuestPlanner.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Quests/NpcLocator.h"
#include "Characters/NpcCharacter.h"

// Sets default values for this component's properties
UQuestActivator::UQuestActivator()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UQuestActivator::UpdateQuestStatus(FString questName, FString dialogId)
{
	QuestPlanner->SetQuestsToUpdate();
	UQuestGoal** questToAdd = UnlockedQuests.Find(questName);
	if (questToAdd)
	{
		UnlockedQuests.Remove(questName);
		QuestPlanner->AddOrUpdateQuest(*questToAdd);
	}
}

void UQuestActivator::Initialize()
{
	ActivateQuestRequirement(FString("Start"));
	QuestPlanner->SetQuestsToUpdate();
	
}


// Called when the game starts
void UQuestActivator::BeginPlay()
{
	Super::BeginPlay();



	WorldStates = GetOwner()->GetComponentByClass<UBlackboardComponent>();
	QuestPlanner = GetOwner()->GetComponentByClass<UQuestPlanner>();
	for (TSubclassOf<UQuestGoal>& questClass : QuestClasses)
	{		
		Quests.Add(NewObject<UQuestGoal>(this, questClass));	
	}

	BuildRequrementMap();	
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UQuestActivator::Initialize);
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
		UnlockQuest(requiredQuest);
	}
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

void UQuestActivator::UnlockQuest(UQuestGoal* quest)
{
	if (quest->RequirementsLeft() <= 0)
	{

		quest->OnQuestCompleted.BindUObject(this, &UQuestActivator::ActivateQuestRequirement);
		UNpcLocator* npcLocator = Cast<UNpcLocator>(WorldStates->GetValueAsObject("NpcLocator"));
		if (npcLocator)
		{
			ANpcCharacter* npc = npcLocator->GetNpc(quest->GetQuestGiver());
			if (npc)
			{
				npc->AddUnlockedQuest(quest->GetQuestName());
				quest->ExecuteEffects(WorldStates);
				UnlockedQuests.Add(quest->GetQuestName(), quest);
			}
			else
			{
				quest->ExecuteEffects(WorldStates);
				QuestPlanner->AddOrUpdateQuest(quest);
			}
		}		
	}
}
