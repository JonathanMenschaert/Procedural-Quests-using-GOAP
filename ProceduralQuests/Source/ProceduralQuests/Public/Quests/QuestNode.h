#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "QuestNode.generated.h"

class UQuestAction;

UCLASS()
class PROCEDURALQUESTS_API UQuestNode : public UObject
{
	GENERATED_BODY()

public:

	void SetNodeAction(UQuestAction* action);
	void AddConnectedNode(UQuestNode* node);
	
	UQuestAction* GetNodeAction() const;
	TArray<UQuestNode*> GetConnectedNodes() const;
	bool HasConnectedNodes() const;
	
private:

	UPROPERTY()
	UQuestAction* Action;

	UPROPERTY()
	TArray<UQuestNode*> Connections;

};
