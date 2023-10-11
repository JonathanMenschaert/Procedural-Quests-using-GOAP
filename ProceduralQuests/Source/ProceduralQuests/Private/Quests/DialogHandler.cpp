#include "Quests/DialogHandler.h"
#include "Game/UI/DialogBoxWidget.h"
// Sets default values for this component's properties
UDialogHandler::UDialogHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
	IsActive = false;
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
	OnDialogEnded.Broadcast(CurrentQuestName, CurrentDialog.DialogId);
	IsActive = false;
}


void UDialogHandler::InitiateDialog(const FDialog& dialog, const FString& questName)
{
	IsActive = true;
	CurrentDialog = dialog;
	CurrentIdx = 0;
	CurrentQuestName = questName;
	DialogBoxWidget = CreateWidget<UDialogBoxWidget>(GetWorld(), DialogBoxWidgetClass);
	DialogBoxWidget->AddToViewport();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UDialogHandler::NextLine);
}

bool UDialogHandler::HasDialogActive() const
{
	return IsActive;;
}

