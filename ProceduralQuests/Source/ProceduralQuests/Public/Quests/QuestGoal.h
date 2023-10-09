#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestGoal.generated.h"


class UWorldStateModifier;

UCLASS(Blueprintable, BlueprintType)
class PROCEDURALQUESTS_API UQuestGoal : public UObject
{
	GENERATED_BODY()

public:

	virtual const TArray<TSubclassOf<UWorldStateModifier>>& GetConditions() const;
	void SetCompleted(bool complete);
	bool IsCompleted() const;

	void CompleteQuest();

	UFUNCTION(BlueprintCallable)
	const FString& GetQuestName() const;

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

	UPROPERTY(EditAnywhere, Category = "General Settings")
	TArray<TSubclassOf<UWorldStateModifier>> Conditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	TArray<FString> Requirements;


	bool IsQuestCompleted;
};
