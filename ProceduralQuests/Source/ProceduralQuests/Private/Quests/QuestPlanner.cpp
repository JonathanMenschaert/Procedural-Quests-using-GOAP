// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestPlanner.h"
#include "Quests/QuestAction.h"
#include "Quests/QuestGoal.h"
#include "Quests/QuestNode.h"
#include "Quests/WorldStateModifier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Inventory.h"
#include "Game/UI/ObjectiveWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/UI/QuestLogWidget.h"

// Sets default values for this component's properties
UQuestPlanner::UQuestPlanner()
{
	//Planner does not need to tick
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UQuestPlanner::AddQuest(TSubclassOf<UQuestGoal> quest)
{
	//Goals.AddUnique(quest);
	UQuestGoal* goal = Cast<UQuestGoal>(quest->GetDefaultObject());
	if (!goal)
	{
		return;
	}
	if (goal->IsCompleted())
	{
		ActiveQuests.Remove(quest);
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
	SelectedQuest = quest;
}

void UQuestPlanner::SetObjectiveWidget(UObjectiveWidget* objective)
{
	ObjectiveWidget = objective;
}


void UQuestPlanner::UpdateQuests()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Updating Quests...");
	TArray<TSubclassOf<UQuestGoal>> questsToRecalculate{ TArray<TSubclassOf<UQuestGoal>>() };

	for (TPair<TSubclassOf<UQuestGoal>, FObjectives>& pair : ActiveQuests)
	{
		
		FObjectives& currentObjective{ pair.Value };
		int& currentActionIdx{ currentObjective.CurrentAction };

		bool questUpdating{ true };
		while (questUpdating)
		{
			
			UQuestAction* action = currentObjective.Actions[currentActionIdx];
			//1. check if action has the correct state for the precondition
			if (!action->IsValid(WorldStates))
			{
				//1.1 go back to previous idx if possible
				if (currentActionIdx > 0)
				{
					--currentActionIdx;
					continue;
				}
				// set the quest to recalculate if the idx is already at 0 and continue to the next quest
				else
				{
					questsToRecalculate.Add(pair.Key);
					questUpdating = false;
				}
				//1.2 repeat from 1
			}

			bool resetObjective{ false };

			//2. Check if action has the correct state for the effect
			if (questUpdating && action->Execute(WorldStates))
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
					questsToRecalculate.Add(pair.Key);
					resetObjective = true;
				}
			}

			if (pair.Key == SelectedQuest && ObjectiveWidget)
			{
				if (!resetObjective)
				{
					ObjectiveWidget->SetCurrentObjective(currentObjective.Actions[currentActionIdx]->GetObjectives());
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "set objective");
				}
				else
				{
					ObjectiveWidget->SetCurrentObjective(FString("Select new Quest"));
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Reset objective");
				}
			}

			questUpdating = false;
		}
	}

	for (TSubclassOf<UQuestGoal>& quest : questsToRecalculate)
	{
		AddQuest(quest);
	}
}

void UQuestPlanner::OpenQuestLog()
{
	bool isQuestLogOpen{ QuestLogWidget != nullptr};
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (isQuestLogOpen)
	{
		SelectedQuest = QuestLogWidget->GetSelectedQuest();

		QuestLogWidget->RemoveFromParent();
		QuestLogWidget = nullptr;
		FInputModeGameOnly inputMode{};
		controller->SetInputMode(inputMode);
	}
	else
	{
		QuestLogWidget = CreateWidget<UQuestLogWidget>(GetWorld(), QuestLogWidgetClass);

		TArray<TSubclassOf<UQuestGoal>> quests{};
		for (TPair<TSubclassOf<UQuestGoal>, FObjectives>& pair : ActiveQuests)
		{				
			quests.AddUnique(pair.Key);			
		}
		QuestLogWidget->OpenQuestLog(quests, SelectedQuest);
		QuestLogWidget->AddToViewport();
		FInputModeGameAndUI inputMode{};
		inputMode.SetWidgetToFocus(QuestLogWidget->GetCachedWidget());
		controller->SetInputMode(inputMode);
		
	}

	if (ObjectiveWidget)
	{
		
		ObjectiveWidget->SetVisibility(isQuestLogOpen ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}

	controller->SetShowMouseCursor(!isQuestLogOpen);
	controller->SetIgnoreLookInput(!isQuestLogOpen);
	controller->SetIgnoreMoveInput(!isQuestLogOpen);

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
	for (TSubclassOf<UQuestGoal>& quest : Goals)
	{
		AddQuest(quest);
	}
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UQuestPlanner::UpdateQuests, 0.15f, false);

	
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

