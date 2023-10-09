// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestStatus.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALQUESTS_API UQuestStatus : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestStatus();

	//Used to receive the quest status from a dialog ending
	UFUNCTION()
	void UpdateQuestStatus(FString questName, FString dialogId);

	const FString& GetStatus(const FString& questName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<FString, FString> QuestStates;

};
