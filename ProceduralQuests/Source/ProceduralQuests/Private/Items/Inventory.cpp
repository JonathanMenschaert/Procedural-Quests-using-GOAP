// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	
}

void UInventory::AddItem(const FString& name, int amount)
{
	if (Items.Contains(name))
	{
		int storedAmount = Items[name];
		Items.Add(name, storedAmount + amount);
	}
	else
	{
		Items.Add(name, amount);
	}
	OnInventoryChanged.Broadcast();
}

//Rework this later
void UInventory::UseItem(const FString& name)
{
	if (Items.Contains(name))
	{
		int value = --Items[name];
		if (value == 0)
		{
			Items.Remove(name);
		}
	}
	OnInventoryChanged.Broadcast();
}

bool UInventory::HasItem(const FString& name, int amount)
{
	if (Items.Contains(name))
	{
		if (Items[name] >= amount)
		{
			return true;
		}
	}
	return false;
}

bool UInventory::RemoveItem(const FString& name, int amount)
{
	if (Items.Contains(name))
	{
		int value = Items[name];
		if (value < amount)
		{
			return false;
		}

		value -= amount;

		if (value == 0)
		{
			Items.Remove(name);
		}
		else
		{
			Items[name] = value;
		}
		OnInventoryChanged.Broadcast();
		return true;
	}
	return false;
}

void UInventory::PrintAllItems() const
{
	if (!GEngine)
	{
		return;
	}
	for (const TPair<FString, int>& pair : Items)
	{
		pair.Key;
		pair.Value;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, pair.Key + " " + FString::FromInt(pair.Value));
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "All Items printed");
}

