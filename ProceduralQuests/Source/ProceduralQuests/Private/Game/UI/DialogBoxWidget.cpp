// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/DialogBoxWidget.h"

void UDialogBoxWidget::SetDialogLine(const FString& line)
{
	OnDialogLineSent.Broadcast(line);
}
