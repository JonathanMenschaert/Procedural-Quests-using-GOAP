// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class ABaseItem;
class UBillboardComponent;

UCLASS()
class PROCEDURALQUESTS_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* Billboard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnItem();


	UFUNCTION()
	void OnItemDestroyed(AActor* actor);

	UPROPERTY()
	ABaseItem* ItemObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<ABaseItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int MaxItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnInterval;

	UPROPERTY()
	TArray<ABaseItem*> SpawnedItems;

	bool IsSpawning;
};
