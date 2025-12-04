#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "SmartTaggerBlueprintLibrary.generated.h"

UCLASS()
class SMARTTAGGER_API USmartTaggerBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Smart Tagger")
	static void SmartApplyTags(const TArray<AActor*>& Actors, const TArray<FName>& Tags, bool bAppend);
};
