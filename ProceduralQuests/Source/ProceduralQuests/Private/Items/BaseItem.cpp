// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Items/Inventory.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Item Collision"));
	RootComponent = SphereCollider;
	SphereCollider->InitSphereRadius(40.0f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);
	
}

void ABaseItem::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	

	APlayerCharacter* pPlayer{ Cast<APlayerCharacter>(otherActor) };
	if (!pPlayer)
	{
		return;
	}

	UInventory* pInventory{ pPlayer->GetComponentByClass<UInventory>() };
	if (!pInventory)
	{
		return;
	}

	pInventory->AddItem(Name, Amount);
	Destroy();
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

