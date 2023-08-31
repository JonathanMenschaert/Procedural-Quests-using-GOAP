// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestPlanner.h"
#include "Quests/QuestAction.h"
#include "BehaviorTree/BlackboardData.h"

// Sets default values for this component's properties
UQuestPlanner::UQuestPlanner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UQuestPlanner::GenerateQuest()
{
	//Generate quest here

}


// Called when the game starts
void UQuestPlanner::BeginPlay()
{
	Super::BeginPlay();

	WorldStates = GetOwner()->GetComponentByClass<UBlackboardComponent>();
}


// Called every frame
void UQuestPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

