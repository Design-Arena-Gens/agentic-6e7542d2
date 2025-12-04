#include "SmartTaggerBlueprintLibrary.h"

#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "ScopedTransaction.h"

void USmartTaggerBlueprintLibrary::SmartApplyTags(const TArray<AActor*>& Actors, const TArray<FName>& Tags, bool bAppend)
{
#if WITH_EDITOR
	if (!GEditor)
	{
		return;
	}

	const FScopedTransaction Transaction(NSLOCTEXT("SmartTagger", "BlueprintApplyTags", "Smart Tagger Blueprint Apply Tags"));

	for (AActor* Actor : Actors)
	{
		if (!IsValid(Actor))
		{
			continue;
		}

		Actor->Modify();

		if (!bAppend)
		{
			Actor->Tags.Empty();
		}

		for (const FName& Tag : Tags)
		{
			if (!Tag.IsNone())
			{
				Actor->Tags.AddUnique(Tag);
			}
		}
	}
#endif
}
