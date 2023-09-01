// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AddItemToInventory(const FString& name, int amount)
{
	Items[name] = Items[name] + amount;
}

void UInventory::UseItemFromInventory(const FString& name)
{
	if (Items.Contains(name))
	{
		int value = --Items[name];
		if (value == 0)
		{
			Items.Remove(name);
		}
	}
}

