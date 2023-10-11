// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/States/DialogModifier.h"
#include "Quests/NpcLocator.h"
#include "Characters/NpcCharacter.h"
#include "Quests/QuestStatus.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDialogModifier::ChangeState(UBlackboardComponent* blackboard) const
{
	UNpcLocator* npcLocator = Cast<UNpcLocator>(blackboard->GetValueAsObject("NpcLocator"));
	if (npcLocator)
	{
		ANpcCharacter* npc = npcLocator->GetNpc(NpcName);
		npc->SetNewDialog(QuestName, Dialog);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "new dialog set");
		return true;
	}
	return false;
}

bool UDialogModifier::HasState(const UBlackboardComponent* blackboard) const
{
	UQuestStatus* questStatus = Cast<UQuestStatus>(blackboard->GetValueAsObject("QuestStatus"));
	if (questStatus)
	{
		return questStatus->GetStatus(QuestName) == Dialog.DialogId;
	}
	return false;
}

bool UDialogModifier::Compare(UWorldStateModifier* state)
{
	UDialogModifier* dialogState = Cast<UDialogModifier>(state);
	if (!dialogState)
	{
		return false;
	}
	return Dialog.DialogId == dialogState->Dialog.DialogId;
}

FString UDialogModifier::GetObjective() const
{
	return FString("Talk to " + NpcName);
}
