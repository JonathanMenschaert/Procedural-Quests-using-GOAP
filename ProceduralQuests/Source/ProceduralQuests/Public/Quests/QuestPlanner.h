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
	bool AddOrUpdateQuest(UQuestGoal* quest);

	UFUNCTION()
	void SetQuestsToUpdate();

	bool GenerateQuest(UQuestNode* node, const TArray<TSubclassOf<UWorldStateModifier>>& conditions);
	int FindCheapestAction(UQuestNode* node, TArray<UQuestAction*>& actions);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateSelectedQuest();

	UFUNCTION()
	void SetSelectedQuest(UQuestGoal* quest);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
	TArray<TSubclassOf<UQuestAction>> Actions;

	UPROPERTY()
	UBlackboardComponent* WorldStates;

	UPROPERTY()
	TMap<UQuestGoal*, UQuestAction*> ActiveQuests;

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
