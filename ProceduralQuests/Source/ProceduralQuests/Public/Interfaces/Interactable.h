#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Quests/Dialog.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class PROCEDURALQUESTS_API IInteractable
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(FString& request, FDialog& outDialog);
};
