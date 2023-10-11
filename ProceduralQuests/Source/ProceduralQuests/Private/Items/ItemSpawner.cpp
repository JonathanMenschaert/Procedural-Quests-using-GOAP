// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemSpawner.h"
#include "Items/BaseItem.h"
#include "Components/BillboardComponent.h"
#include "TimerManager.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));

	SpawnRadius = 300.f;
	MaxItems = 5;
	SpawnInterval = 1.f;
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	ItemObject = Cast<ABaseItem>(ItemClass->GetDefaultObject());
	SpawnItem();
}

void AItemSpawner::SpawnItem()
{
	ABaseItem* item = GetWorld()->SpawnActor<ABaseItem>(ItemClass, FTransform{});
	item->OnDestroyed.AddDynamic(this, &AItemSpawner::OnItemDestroyed);
	item->SetActorLocation(GetActorLocation() + FVector{ FMath::RandRange(-SpawnRadius, SpawnRadius), FMath::RandRange(-SpawnRadius, SpawnRadius), 0.f });
	SpawnedItems.Add(item);
	if (SpawnedItems.Num() < MaxItems)
	{
		FTimerHandle unusedHandle{};
		GetWorld()->GetTimerManager().SetTimer(unusedHandle, this, &AItemSpawner::SpawnItem, SpawnInterval, false);
	}
}

void AItemSpawner::OnItemDestroyed(AActor* actor)
{
	FTimerHandle unusedHandle{};
	GetWorld()->GetTimerManager().SetTimer(unusedHandle, this, &AItemSpawner::SpawnItem, SpawnInterval, false);
}

