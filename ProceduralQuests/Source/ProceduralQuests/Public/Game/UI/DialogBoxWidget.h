#pragma once

#include "CoreMinimal.h"
#include "Game/UI/BaseWidget.h"
#include "DialogBoxWidget.generated.h"

UCLASS()
class PROCEDURALQUESTS_API UDialogBoxWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	void SetDialogLine(const FString& line);

protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogLineSent, FString, Line);
	UPROPERTY(BlueprintAssignable, Category = "Dialog")
	FOnDialogLineSent OnDialogLineSent;
};
