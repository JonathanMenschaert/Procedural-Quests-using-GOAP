#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestActivatorComponent.generated.h"

class UQuestGoal;
class UQuestPlanner;
class UBlackboardComponent;
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

	UFUNCTION()
	void UpdateQuestStatus(FString questName, FString dialogId);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void ActivateQuestRequirement(FString questName);

	UFUNCTION()
	void BuildRequrementMap();

	UFUNCTION()
	void UnlockQuest(UQuestGoal* quest);

	UFUNCTION()
	void ExecuteQuestEffects(UQuestGoal* quest);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<TSubclassOf<UQuestGoal>> QuestClasses;

	UPROPERTY()
	TArray<UQuestGoal*> Quests;

	UPROPERTY()
	TMap<FString, FRequirements> RequirementMap;

	UPROPERTY()
	UQuestPlanner* QuestPlanner;		

private:

	UPROPERTY()
	TMap<FString, UQuestGoal*> UnlockedQuests;

	UPROPERTY()
	UBlackboardComponent* WorldStates;
};
