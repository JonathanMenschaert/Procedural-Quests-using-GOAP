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

bool UInventoryModifier::Compare(UWorldStateModifier* state)
{
	UInventoryModifier* inventoryState = Cast<UInventoryModifier>(state);
	if (!inventoryState)
	{
		return false;
	}
	return Item == inventoryState->Item && Amount == inventoryState->Amount;
}

FString UInventoryModifier::GetObjective() const
{
	return FString("Collect " + FString::FromInt(Amount) + " " + Item);
}
