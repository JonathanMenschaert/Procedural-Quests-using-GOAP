// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestPlanner.generated.h"

class UQuestAction;
class UQuestGoal;
class UQuestNode;
class UBlackboardComponent;
class UWorldStateModifier;
class UObjectiveWidget;
USTRUCT()
struct FObjectives
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UQuestAction*> Actions{};

	int CurrentAction{};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALQUESTS_API UQuestPlanner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestPlanner();

	UFUNCTION()
	void UpdateQuests();
	UBlackboardComponent* GetBlackboard() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
	TArray<TSubclassOf<UQuestAction>> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goals")
	TArray<TSubclassOf<UQuestGoal>> Goals;

	UPROPERTY()
	UBlackboardComponent* WorldStates;

	UPROPERTY()
	TMap<TSubclassOf<UQuestGoal>, FObjectives> ActiveQuests;


	TSubclassOf<UQuestGoal> SelectedQuest;

	UObjectiveWidget* ObjectiveWidget;

	bool GenerateQuest(UQuestNode* node, const TArray<TSubclassOf<UWorldStateModifier>>& conditions);
	int FindCheapestRoute(UQuestNode* node, TArray<UQuestAction*>& actions);
	void AddQuest(TSubclassOf<UQuestGoal> quest);



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetObjectiveWidget(UObjectiveWidget* objective);
		
};
