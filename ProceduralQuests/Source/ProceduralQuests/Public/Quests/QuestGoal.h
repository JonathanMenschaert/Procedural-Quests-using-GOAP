#pragma once

#include "CoreMinimal.h"
#include "QuestAction.h"
#include "QuestGoal.generated.h"


class UWorldStateModifier;

UCLASS(Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UQuestGoal : public UQuestAction
{
	GENERATED_BODY()

public:

	UQuestGoal();
	void SetCompleted(bool complete);
	bool IsCompleted() const;

	void CompleteQuest();

	UFUNCTION(BlueprintCallable)
	const FString& GetQuestName() const;

	const FString& GetQuestGiver() const;

	UFUNCTION()
	void RemoveRequirement(const FString& requirement);

	UFUNCTION()
	int RequirementsLeft() const;

	UFUNCTION()
	const TArray<FString>& GetQuestRequirements() const;

	UFUNCTION()
	void NotifyQuestCompleted();

	DECLARE_DELEGATE_OneParam(FOnQuestCompleted, FString);
	FOnQuestCompleted OnQuestCompleted;

protected:


	UPROPERTY(EditAnywhere, Category = "General Settings")
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	TArray<FString> Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FString QuestGiver;


	bool IsQuestCompleted;
};
