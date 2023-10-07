// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/BaseWidget.h"
#include "QuestLogWidget.generated.h"

/**
 * 
 */

class UQuestGoal;
UCLASS()
class PROCEDURALQUESTS_API UQuestLogWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UQuestLogWidget(const FObjectInitializer& objectInitializer);

	void OpenQuestLog(const TArray<UQuestGoal*>& quests, UQuestGoal* currentQuest);

	UFUNCTION(BlueprintCallable)
	UQuestGoal* GetSelectedQuest() const;

protected:

	UFUNCTION(BlueprintCallable)
	UQuestGoal* SetSelectedQuest(int index);

	UFUNCTION(BlueprintCallable)
	UQuestGoal* GetQuestByIndex(int index);

	UFUNCTION(BlueprintCallable)
	int GetQuestLogSize() const;
	
	TArray<UQuestGoal*> Quests;

	UQuestGoal*  CurrentQuest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestLogOpened);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuestLogOpened OnQuestLogOpened;

};
