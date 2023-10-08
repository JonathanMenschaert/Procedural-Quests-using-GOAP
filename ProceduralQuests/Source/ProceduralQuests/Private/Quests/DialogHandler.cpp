// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/DialogHandler.h"

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
	GEngine->AddOnScreenDebugMessage(-1, timeTillNextLine, FColor::Emerald, CurrentDialog.Lines[CurrentIdx]);
	++CurrentIdx;
	FTimerHandle unusedHandle{};
	GetWorld()->GetTimerManager().SetTimer(unusedHandle, this, &UDialogHandler::NextLine, timeTillNextLine, false);
}


// Called every frame
void UDialogHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogHandler::InitiateDialog(const FDialog& dialog)
{
	CurrentDialog = dialog;
	CurrentIdx = 0;
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UDialogHandler::NextLine);
}

