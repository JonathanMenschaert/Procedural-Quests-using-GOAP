// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestManager.h"
#include "Quests/QuestPlanner.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Quests/QuestActivatorComponent.h"
#include "Quests/NpcLocator.h"

// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	QuestPlannerComponent = CreateDefaultSubobject<UQuestPlanner>(TEXT("Quest Planner"));
	QuestActivatorComponent = CreateDefaultSubobject<UQuestActivator>(TEXT("Quest Activator"));
	NpcLocatorComponent = CreateDefaultSubobject<UNpcLocator>(TEXT("Npc Locator"));
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
}

UBlackboardComponent* AQuestManager::GetBlackboard()
{
	return BlackboardComponent;
}

UQuestPlanner* AQuestManager::GetQuestPlanner()
{
	return QuestPlannerComponent;
}

UNpcLocator* AQuestManager::GetNpcLocator()
{
	return NpcLocatorComponent;
}

