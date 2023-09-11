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
	//Planner does not need to tick
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UQuestPlanner::AddQuest(TSubclassOf<UQuestGoal> quest)
{
	Goals.AddUnique(quest);
	UQuestGoal* goal = Cast<UQuestGoal>(quest->GetDefaultObject());
	if (!goal || goal->IsCompleted())
	{
		return;
	}

	UQuestNode* node = NewObject<UQuestNode>();
	node->SetNodeAction(nullptr);
	if (!GenerateQuest(node, goal->GetConditions()))
	{
		return;
	}

	TArray<UQuestAction*> actions = TArray<UQuestAction*>();
	FindCheapestRoute(node, actions);

	ActiveQuests.Add(quest, FObjectives{ actions });
}

void UQuestPlanner::UpdateQuests()
{
	UInventory* inventory = Cast<UInventory>(WorldStates->GetValueAsObject(FName("Inventory")));
	if (inventory)
	{
		inventory->PrintAllItems();
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Updating Quests...");
	TArray<TSubclassOf<UQuestGoal>> questsToRecalculate{ TArray<TSubclassOf<UQuestGoal>>() };

	for (TPair<TSubclassOf<UQuestGoal>, FObjectives>& pair : ActiveQuests)
	{
		FObjectives& currentObjective{ pair.Value };
		int& currentActionIdx{ currentObjective.CurrentAction };

		while (true)
		{
			UQuestAction* action = currentObjective.Actions[currentActionIdx];
			//1. check if action has the correct state for the precondition
			if (!action->IsValid(WorldStates))
			{
				//1.1 go back to previous idx if possible
				if (currentActionIdx > 0)
				{
					--currentActionIdx;
				}
				// set the quest to recalculate if the idx is already at 0 and continue to the next quest
				else
				{
					questsToRecalculate.Add(pair.Key);
				}
				//1.2 repeat from 1
				continue;
			}
			//2. Check if action has the correct state for the effect
			if (action->Execute(WorldStates))
			{
				//2.1 increase the action idx, if it surpasses the action list length, set quest as completed.
				if (currentActionIdx < pair.Value.Actions.Num() - 1)
				{
					++currentActionIdx;
				}
				else
				{
					UQuestGoal* goal = Cast<UQuestGoal>(pair.Key->GetDefaultObject());
					goal->SetCompleted(true);
					ActiveQuests.Remove(pair.Key);
				}
			}
			//2.2 do nothing and continue to the next quest if it doesn't match
		}
	}

	for (TSubclassOf<UQuestGoal>& quest : questsToRecalculate)
	{
		AddQuest(quest);
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

					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Building node...");

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

int UQuestPlanner::FindCheapestRoute(UQuestNode* node, TArray<UQuestAction*>& actions)
{
	const TArray<UQuestNode*>& connectedNodes{ node->GetConnectedNodes() };
	int minCost = connectedNodes.Num() > 0 ? INT32_MAX : 0;
	for (UQuestNode* connection : connectedNodes)
	{
		TArray<UQuestAction*> questActions = TArray<UQuestAction*>();
		int cost = FindCheapestRoute(connection, questActions);

		if (cost < minCost)
		{
			minCost = cost;
			actions = questActions;
		}
	}
	
	UQuestAction* action = node->GetNodeAction();
	if (action)
	{
		actions.Add(action);
		minCost += action->GetCost();
	}

	return minCost;
}




// Called every frame
void UQuestPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

