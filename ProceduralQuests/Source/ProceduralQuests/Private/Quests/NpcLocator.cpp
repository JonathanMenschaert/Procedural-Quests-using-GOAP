// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/NpcLocator.h"
#include "Characters/NpcCharacter.h"
// Sets default values for this component's properties
UNpcLocator::UNpcLocator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UNpcLocator::AddNpc(ANpcCharacter* npc)
{
	StoredNpcs.Add(npc->GetNpcName(), npc);
}

ANpcCharacter* UNpcLocator::GetNpc(const FString& npcName)
{
	ANpcCharacter** npc = StoredNpcs.Find(npcName);
	if (!npc)
	{
		return nullptr;
	}
	return *StoredNpcs.Find(npcName);
}


// Called when the game starts
void UNpcLocator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


