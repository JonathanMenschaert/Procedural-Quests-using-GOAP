#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Dialog.h"
#include "DialogHandler.generated.h"

class UDialogBoxWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALQUESTS_API UDialogHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogHandler();

	void InitiateDialog(const FDialog& dialog, const FString& questName);

	UPROPERTY()
	FDialog CurrentDialog;

	int CurrentIdx;

	FString CurrentQuestName;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogEnded, FString, questName, FString, dialogId);
	UPROPERTY(BlueprintAssignable, Category = "Dialog")
	FOnDialogEnded OnDialogEnded;

protected:

	UFUNCTION()
	void NextLine();
	
	UFUNCTION()
	void EndDialog();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UDialogBoxWidget> DialogBoxWidgetClass;

	UPROPERTY()
	UDialogBoxWidget* DialogBoxWidget;

	
};
