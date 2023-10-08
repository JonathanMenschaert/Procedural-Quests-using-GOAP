// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NpcCharacter.h"

ANpcCharacter::ANpcCharacter()
{
}

void ANpcCharacter::BeginPlay()
{

	Dialogs.Add(FString("Default"), DefaultDialog);
}

void ANpcCharacter::Tick(float DeltaTime)
{
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
