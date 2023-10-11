#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "../Quests/Dialog.h"
#include "../Interfaces/Interactable.h"
#include "NpcCharacter.generated.h"

class UTextRenderComponent;
class UBillboardComponent;

UCLASS()
class PROCEDURALQUESTS_API ANpcCharacter : public ABaseCharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(FString& request, FDialog& outDialog);
	virtual void Interact_Implementation(FString& request, FDialog& outDialog);


	void SetNewDialog(const FString& quest, const FDialog& dialog);

	void AddUnlockedQuest(const FString& questName);

	const FString& GetNpcName() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* QuestMarker;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Dialog")
	FDialog DefaultDialog;

	UPROPERTY()
	TMap<FString, FDialog> Dialogs;

	UPROPERTY()
	TArray<FString> UnlockedQuests;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	UTextRenderComponent* NameRenderer;
	
};
