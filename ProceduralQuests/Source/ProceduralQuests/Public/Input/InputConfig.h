#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfig.generated.h"

UCLASS()
class PROCEDURALQUESTS_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	UInputAction* InputRequestQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	UInputAction* InputOpenQuestLog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	UInputAction* InputInteract;
};
