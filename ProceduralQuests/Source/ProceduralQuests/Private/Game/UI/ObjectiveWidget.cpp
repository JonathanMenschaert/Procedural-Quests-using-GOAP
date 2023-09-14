// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/ObjectiveWidget.h"

void UObjectiveWidget::SetCurrentObjective(FString objective)
{
	Objectives = objective;
	OnObjectiveUpdated.Broadcast();
}

void UObjectiveWidget::SetCurrentObjective(TArray<FString> objectives)
{
	 SetCurrentObjective(FString::Join(objectives, TEXT("\n")));
	
}
