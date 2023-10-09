#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "QuestGameInstance.generated.h"

UCLASS()
class PROCEDURALQUESTS_API UQuestGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init();
	
};
