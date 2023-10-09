#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dialog.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FDialog
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float BaseLineDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FString DialogId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<FString> Lines{};
};
