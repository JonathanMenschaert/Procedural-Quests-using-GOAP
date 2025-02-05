#pragma once

#include "CoreMinimal.h"
#include "Quests/WorldStateModifier.h"
#include "InventoryModifier.generated.h"


UCLASS()
class PROCEDURALQUESTS_API UInventoryModifier : public UWorldStateModifier
{
	GENERATED_BODY()

public:
	virtual bool HasState(const UBlackboardComponent* blackboard) const override;
	virtual bool ChangeState(UBlackboardComponent* blackboard) const override;	
	virtual bool Compare(UWorldStateModifier* state) override;
	virtual FString GetObjective() const override;

protected:

	UPROPERTY(EditAnywhere, Category = "Item")
	FString Item;

	UPROPERTY(EditAnywhere, Category = "Item")
	int Amount;
};
