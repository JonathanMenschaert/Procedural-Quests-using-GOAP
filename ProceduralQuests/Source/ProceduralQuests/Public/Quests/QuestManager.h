// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

class UBlackboardComponent;
class UQuestPlanner;

UCLASS()
class PROCEDURALQUESTS_API AQuestManager final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UQuestPlanner* QuestPlannerComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UBlackboardComponent* GetBlackboard();

	UFUNCTION()
	UQuestPlanner* GetQuestPlanner();

};
