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
class UQuestLogWidget;

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
	void OpenQuestLog();

	UFUNCTION()
	void AddQuest(UQuestGoal* quest);

	UFUNCTION()
	void SetQuestsToUpdate();

	bool GenerateQuest(UQuestNode* node, const TArray<TSubclassOf<UWorldStateModifier>>& conditions);
	int FindCheapestRoute(UQuestNode* node, TArray<UQuestAction*>& actions);

	UFUNCTION()
	void UpdateQuestStatus(FString questName, FString dialogId);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateQuests();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
	TArray<TSubclassOf<UQuestAction>> Actions;

	UPROPERTY()
	UBlackboardComponent* WorldStates;

	UPROPERTY()
	TMap<UQuestGoal*, FObjectives> ActiveQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UQuestLogWidget> QuestLogWidgetClass;

	UPROPERTY()
	UQuestGoal* SelectedQuest;

	UPROPERTY()
	UObjectiveWidget* ObjectiveWidget;

	UPROPERTY()
	UQuestLogWidget* QuestLogWidget;

private:

	bool MarkQuestsAsDirty;

};
