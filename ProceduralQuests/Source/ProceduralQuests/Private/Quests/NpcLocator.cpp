#include "Quests/NpcLocator.h"
#include "Characters/NpcCharacter.h"

UNpcLocator::UNpcLocator()
{
	
	PrimaryComponentTick.bCanEverTick = false;
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


