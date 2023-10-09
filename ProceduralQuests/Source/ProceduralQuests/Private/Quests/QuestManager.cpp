#include "Quests/QuestManager.h"
#include "Quests/QuestPlanner.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Quests/QuestActivatorComponent.h"
#include "Quests/NpcLocator.h"
#include "Quests/QuestStatus.h"


AQuestManager::AQuestManager()
{
	PrimaryActorTick.bCanEverTick = false;
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	QuestPlannerComponent = CreateDefaultSubobject<UQuestPlanner>(TEXT("Quest Planner"));
	QuestActivatorComponent = CreateDefaultSubobject<UQuestActivator>(TEXT("Quest Activator"));
	NpcLocatorComponent = CreateDefaultSubobject<UNpcLocator>(TEXT("Npc Locator"));
	QuestStatusComponent = CreateDefaultSubobject<UQuestStatus>(TEXT("Quest Status"));
}

void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
	BlackboardComponent->SetValueAsObject(FName("NpcLocator"), NpcLocatorComponent);
	BlackboardComponent->SetValueAsObject(FName("QuestStatus"), QuestStatusComponent);
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

