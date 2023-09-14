// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALQUESTS_API UObjectiveWidget : public UUserWidget
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
