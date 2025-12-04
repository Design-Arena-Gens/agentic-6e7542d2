#include "SmartTaggerCommands.h"

#include "ToolMenus.h"

void FSmartTaggerCommands::RegisterCommands()
{
	UI_COMMAND(ExecuteQuickTagger, "Smart Tagger", "Open the Smart Tagger window", EUserInterfaceActionType::Button, FInputChord(EKeys::T, EModifierKey::Alt));
}
