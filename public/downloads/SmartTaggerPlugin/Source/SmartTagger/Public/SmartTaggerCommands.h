#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SmartTaggerStyle.h"

class FSmartTaggerCommands : public TCommands<FSmartTaggerCommands>
{
public:
	FSmartTaggerCommands()
		: TCommands<FSmartTaggerCommands>(
			  TEXT("SmartTagger"),
			  NSLOCTEXT("Contexts", "SmartTagger", "Smart Tagger"),
			  NAME_None,
			  FSmartTaggerStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> ExecuteQuickTagger;
};
