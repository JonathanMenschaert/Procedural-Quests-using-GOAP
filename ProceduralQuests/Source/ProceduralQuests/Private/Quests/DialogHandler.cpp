// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/DialogHandler.h"
#include "Game/UI/DialogBoxWidget.h"
// Sets default values for this component's properties
UDialogHandler::UDialogHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDialogHandler::NextLine()
{
	float timeTillNextLine = CurrentDialog.BaseLineDuration * CurrentDialog.Lines[CurrentIdx].Len();
	const FString& line = CurrentDialog.Lines[CurrentIdx];
	GEngine->AddOnScreenDebugMessage(-1, timeTillNextLine, FColor::Emerald, line);
	if (DialogBoxWidget)
	{
		DialogBoxWidget->SetDialogLine(line);
	}
	++CurrentIdx;
	FTimerHandle unusedHandle{};
	if (CurrentIdx < CurrentDialog.Lines.Num())
	{		
		GetWorld()->GetTimerManager().SetTimer(unusedHandle, this, &UDialogHandler::NextLine, timeTillNextLine, false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(unusedHandle, this, &UDialogHandler::EndDialog, timeTillNextLine, false);
		
	}
}

void UDialogHandler::EndDialog()
{
	DialogBoxWidget->RemoveFromParent();
	DialogBoxWidget = nullptr;
}


void UDialogHandler::InitiateDialog(const FDialog& dialog)
{
	CurrentDialog = dialog;
	CurrentIdx = 0;
	DialogBoxWidget = CreateWidget<UDialogBoxWidget>(GetWorld(), DialogBoxWidgetClass);
	DialogBoxWidget->AddToViewport();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UDialogHandler::NextLine);
}

