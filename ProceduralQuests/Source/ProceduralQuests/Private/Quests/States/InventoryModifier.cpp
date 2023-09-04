// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/States/InventoryModifier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Inventory.h"

bool UInventoryModifier::HasState(const UBlackboardComponent* blackboard) const
{
	UInventory* inventory = Cast<UInventory>(blackboard->GetValueAsObject("Inventory"));
	if (!inventory)
	{
		return false;
	}

	return inventory->HasItem(Item, Amount);
}

bool UInventoryModifier::ChangeState(UBlackboardComponent* blackboard) const
{
	UInventory* inventory = Cast<UInventory>(blackboard->GetValueAsObject("Inventory"));
	if (!inventory)
	{
		return false;
	}

	return inventory->RemoveItem(Item, Amount);
}
