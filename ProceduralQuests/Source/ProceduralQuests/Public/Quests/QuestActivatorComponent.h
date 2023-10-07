// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestActivatorComponent.generated.h"

class UQuestGoal;
class UQuestPlanner;

USTRUCT()
struct FRequirements
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UQuestGoal*> AttachedQuests{};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALQUESTS_API UQuestActivator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestActivator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActivateQuestRequirement(FString questName);

	UFUNCTION()
	void BuildRequrementMap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<TSubclassOf<UQuestGoal>> QuestClasses;

	UPROPERTY()
	TArray<UQuestGoal*> Quests;

	UPROPERTY()
	TMap<FString, FRequirements> RequirementMap;

	UPROPERTY()
	UQuestPlanner* QuestPlanner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
