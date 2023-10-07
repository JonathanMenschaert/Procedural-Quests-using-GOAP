// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestManager.h"
#include "Quests/QuestPlanner.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	QuestPlannerComponent = CreateDefaultSubobject<UQuestPlanner>(TEXT("Quest Planner"));
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBlackboardComponent* AQuestManager::GetBlackboard()
{
	return BlackboardComponent;
}

UQuestPlanner* AQuestManager::GetQuestPlanner()
{
	return QuestPlannerComponent;
}

