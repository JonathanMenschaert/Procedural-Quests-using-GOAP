// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestPlanner.h"
#include "Quests/QuestAction.h"
#include "Quests/QuestGoal.h"
#include "Quests/QuestNode.h"
#include "Quests/WorldStateModifier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Inventory.h"

// Sets default values for this component's properties
UQuestPlanner::UQuestPlanner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UQuestPlanner::UpdateQuests()
{
	UInventory* inventory = Cast<UInventory>(WorldStates->GetValueAsObject(FName("Inventory")));
	if (inventory)
	{
		inventory->PrintAllItems();
	}

	for (TSubclassOf<UQuestGoal>& goalClass : Goals)
	{
		UQuestGoal* goal = Cast<UQuestGoal>(goalClass->GetDefaultObject());
		if (!goal || goal->IsCompleted() )
		{
			continue;
		}
		
		UQuestNode* node = NewObject<UQuestNode>();
		node->SetNodeAction(nullptr);
		if (!GenerateQuest(node, goal->GetConditions()))
		{
			continue;
		}
	}
}

UBlackboardComponent* UQuestPlanner::GetBlackboard() const
{
	return WorldStates;
}


// Called when the game starts
void UQuestPlanner::BeginPlay()
{
	Super::BeginPlay();
	WorldStates = GetOwner()->GetComponentByClass<UBlackboardComponent>();
		
}


bool UQuestPlanner::GenerateQuest(UQuestNode* node, const TArray<TSubclassOf<UWorldStateModifier>>& conditions)
{
	for (const TSubclassOf<UWorldStateModifier>& conditionClass : conditions)
	{
		UWorldStateModifier* condition = Cast<UWorldStateModifier>(conditionClass->GetDefaultObject());

		if (condition->HasState(WorldStates))
		{
			continue;
		}

		for (TSubclassOf<UQuestAction>& actionClass : Actions)
		{
			UQuestAction* action = Cast<UQuestAction>(actionClass->GetDefaultObject());

			for (const TSubclassOf<UWorldStateModifier>& effectClass : action->GetEffects())
			{
				UWorldStateModifier* effect = Cast<UWorldStateModifier>(effectClass->GetDefaultObject());

				if (condition->Compare(effect))
				{
					UQuestNode* connection = NewObject<UQuestNode>();
					connection->SetNodeAction(action);
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Building node effect!");
					}



					if (GenerateQuest(connection, action->GetPreconditions()))
					{
						node->AddConnectedNode(connection);
					}
				}
			}
		}
	}
	if (!node->HasConnectedNodes())
	{
		//Making sure the last action is not nullptr
		UQuestAction* nodeAction = node->GetNodeAction();
		if (!nodeAction)
		{
			return false;
		}
	}
	return true;
}

// Called every frame
void UQuestPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

