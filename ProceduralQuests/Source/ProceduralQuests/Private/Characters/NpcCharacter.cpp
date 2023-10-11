// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NpcCharacter.h"
#include "Components/TextRenderComponent.h"
#include "Quests/QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "Quests/NpcLocator.h"
#include "Components/BillboardComponent.h"

ANpcCharacter::ANpcCharacter()
{

	NameRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	NameRenderer->SetupAttachment(RootComponent);

	QuestMarker = CreateDefaultSubobject<UBillboardComponent>(TEXT("QuestMarker"));
	QuestMarker->SetupAttachment(RootComponent);
	QuestMarker->SetHiddenInGame(false);
}

void ANpcCharacter::BeginPlay()
{

	Dialogs.Add(FString("Default"), DefaultDialog);
	NameRenderer->SetText(FText::FromString(Name));

	AQuestManager* questManager = Cast<AQuestManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AQuestManager::StaticClass()));

	if (questManager)
	{
		questManager->GetNpcLocator()->AddNpc(this);
	}	
}

void ANpcCharacter::Interact_Implementation(FString& request, FDialog& outDialog)
{
	
	FDialog* storedDialog = nullptr;
	const FString defaultQuestName = "Default";
	FString questName = "";
	//First check if there is any unlocked quests and try to load the dialog
	while(UnlockedQuests.Num() > 0 && !storedDialog)
	{
		questName = UnlockedQuests[0];
		storedDialog = Dialogs.Find(questName);
		UnlockedQuests.RemoveAt(0);
	}

	if (UnlockedQuests.Num() == 0)
	{
		QuestMarker->SetVisibility(false);
	}

	//return the dialog if dialog is found, otherwise use the selected quest.
	if (storedDialog)
	{
		request = questName;
		outDialog = *storedDialog;
		return;
	}
	else
	{
		storedDialog = Dialogs.Find(request);
	}

	//If the requested dialog is not found, return the default dialog of the npc.
	if (!storedDialog)
	{
		request = defaultQuestName;
		storedDialog = Dialogs.Find(defaultQuestName);
	}
	outDialog = *storedDialog;
}

void ANpcCharacter::SetNewDialog(const FString& quest, const FDialog& dialog)
{
	Dialogs.Add(quest, dialog);
}

void ANpcCharacter::AddUnlockedQuest(const FString& questName)
{
	QuestMarker->SetVisibility(true);
	UnlockedQuests.Add(questName);
}

const FString& ANpcCharacter::GetNpcName() const
{
	return Name;
}
