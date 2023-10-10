// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NpcCharacter.h"
#include "Components/TextRenderComponent.h"
#include "Quests/QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "Quests/NpcLocator.h"
ANpcCharacter::ANpcCharacter()
{

	NameRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	NameRenderer->SetupAttachment(RootComponent);
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

void ANpcCharacter::Interact_Implementation(const FString& request, FDialog& outDialog)
{
	FDialog* storedDialog = Dialogs.Find(request);
	if (!storedDialog)
	{
		
		storedDialog = Dialogs.Find("Default");
	}

	outDialog = *storedDialog;
}

void ANpcCharacter::SetNewDialog(const FString& quest, const FDialog& dialog)
{
	Dialogs.Add(quest, dialog);
}

const FString& ANpcCharacter::GetNpcName() const
{
	return Name;
}
