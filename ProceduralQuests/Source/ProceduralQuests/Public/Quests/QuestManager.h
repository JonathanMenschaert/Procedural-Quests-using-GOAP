#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

class UBlackboardComponent;
class UQuestPlanner;
class UQuestActivator;
class UNpcLocator;

UCLASS()
class PROCEDURALQUESTS_API AQuestManager final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

	UFUNCTION()
	UBlackboardComponent* GetBlackboard();

	UFUNCTION()
	UQuestPlanner* GetQuestPlanner();

	UFUNCTION()
	UNpcLocator* GetNpcLocator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UQuestPlanner* QuestPlannerComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UQuestActivator* QuestActivatorComponent;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UNpcLocator* NpcLocatorComponent;

};
