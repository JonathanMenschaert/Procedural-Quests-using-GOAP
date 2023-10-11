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

	MarkQuestsAsDirty = false;
}


bool UQuestPlanner::AddOrUpdateQuest(UQuestGoal* quest)
{
	if (!quest)
	{
		return false;
	}

	if (!quest->IsValid(WorldStates))
	{
		quest->CompleteQuest();
	}

	if (quest->IsCompleted())
	{
		ActiveQuests.Remove(quest);
		if (quest == SelectedQuest)
		{
			SelectedQuest = nullptr;
		}
		return false;
	}
	
	UQuestNode* node = NewObject<UQuestNode>();
	node->SetNodeAction(nullptr);
	if (!GenerateQuest(node, quest->GetPreconditions()))
	{
		return false;
	}

	TArray<UQuestAction*> actions = TArray<UQuestAction*>();
	FindCheapestAction(node, actions);

	ActiveQuests.Add(quest, actions[0]);
	return true;
}

void UQuestPlanner::SetQuestsToUpdate()
{
	if (MarkQuestsAsDirty)
	{
		return;
	}
	MarkQuestsAsDirty = true;
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UQuestPlanner::UpdateSelectedQuest);
}

void UQuestPlanner::UpdateSelectedQuest()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Updating Quests...");

	if (!ObjectiveWidget)
	{
		return;
	}
	if (SelectedQuest && AddOrUpdateQuest(SelectedQuest))
	{
		UQuestAction* currentAction = *ActiveQuests.Find(SelectedQuest);
		ObjectiveWidget->SetCurrentObjective(currentAction->GetObjectives());
		currentAction->ExecuteEffects(WorldStates);
		MarkQuestsAsDirty = false;
	}
	else
	{
		ObjectiveWidget->SetCurrentObjective("Select a new quest!");
	}
}

void UQuestPlanner::SetSelectedQuest(UQuestGoal* quest)
{
	
}

void UQuestPlanner::OpenQuestLog()
{
	bool isQuestLogOpen{ QuestLogWidget != nullptr};
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (isQuestLogOpen)
	{
		SelectedQuest = QuestLogWidget->GetSelectedQuest();
		if (SelectedQuest)
		{
			WorldStates->SetValueAsString("CurrentQuest", SelectedQuest->GetQuestName());
			/*FObjectives* objective = ActiveQuests.Find(SelectedQuest);
			objective->Actions[0]*/
		}

		QuestLogWidget->RemoveFromParent();
		QuestLogWidget = nullptr;
		FInputModeGameOnly inputMode{};
		controller->SetInputMode(inputMode);

		UpdateSelectedQuest();
	}
	else
	{
		QuestLogWidget = CreateWidget<UQuestLogWidget>(GetWorld(), QuestLogWidgetClass);

		TArray<UQuestGoal*> quests{};
		for (TPair<UQuestGoal*, UQuestAction*>& pair : ActiveQuests)
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

// Called when the game starts
void UQuestPlanner::BeginPlay()
{
	Super::BeginPlay();
	WorldStates = GetOwner()->GetComponentByClass<UBlackboardComponent>();
	//Display widget
	ObjectiveWidget = CreateWidget<UObjectiveWidget>(GetWorld(), ObjectiveWidgetClass);

	if (ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
	}
}


bool UQuestPlanner::GenerateQuest(UQuestNode* node, const TArray<TSubclassOf<UWorldStateModifier>>& conditions)
{
	for (const TSubclassOf<UWorldStateModifier>& conditionClass : conditions)
	{
		UWorldStateModifier* condition = Cast<UWorldStateModifier>(conditionClass->GetDefaultObject());

		if (condition->HasState(WorldStates))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Already has state");
			continue;
		}

		for (TSubclassOf<UQuestAction>& actionClass : Actions)
		{
			UQuestAction* action = Cast<UQuestAction>(actionClass->GetDefaultObject());

			for (const TSubclassOf<UWorldStateModifier>& effectClass : action->GetResults())
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

int UQuestPlanner::FindCheapestAction(UQuestNode* node, TArray<UQuestAction*>& actions)
{
	const TArray<UQuestNode*>& connectedNodes{ node->GetConnectedNodes() };
	int minCost = connectedNodes.Num() > 0 ? INT32_MAX : 0;
	for (UQuestNode* connection : connectedNodes)
	{
		TArray<UQuestAction*> questActions = TArray<UQuestAction*>();
		int cost = FindCheapestAction(connection, questActions);

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
