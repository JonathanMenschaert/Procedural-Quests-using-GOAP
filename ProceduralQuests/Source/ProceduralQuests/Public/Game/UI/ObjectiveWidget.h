#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "ObjectiveWidget.generated.h"


UCLASS()
class PROCEDURALQUESTS_API UObjectiveWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	void SetCurrentObjective(FString objective);
	void SetCurrentObjective(TArray<FString> objectives);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FString Objectives;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectiveUpdated);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnObjectiveUpdated OnObjectiveUpdated;
};
