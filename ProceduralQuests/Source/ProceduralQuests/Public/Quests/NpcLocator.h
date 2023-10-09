// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NpcLocator.generated.h"

class ANpcCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALQUESTS_API UNpcLocator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNpcLocator();

	void AddNpc(ANpcCharacter* npc);
	ANpcCharacter* GetNpc(const FString& npcName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<FString, ANpcCharacter*> StoredNpcs;
		
};
