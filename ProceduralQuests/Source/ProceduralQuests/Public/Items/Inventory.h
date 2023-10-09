// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALQUESTS_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	void AddItem(const FString& name, int amount = 1);
	void UseItem(const FString& name);
	bool HasItem(const FString& name, int amount = 1);
	bool RemoveItem(const FString& name, int amount = 1);

	//Test function
	void PrintAllItems() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
	UPROPERTY(BlueprintAssignable, Category = "Quests")
	FOnInventoryChanged OnInventoryChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Items")
	TMap<FString, int> Items;
};
