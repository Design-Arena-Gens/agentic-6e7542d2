#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Framework/Commands/UICommandList.h"

class FToolBarBuilder;
class FMenuBuilder;
class SWindow;

class SSmartTaggerPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSmartTaggerPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FReply OnApplyTagsClicked();
	FReply OnRenameClicked();

	bool bAppend = true;
	FString TagString;
	FString MetadataKey;
	FString MetadataValue;
	FString RenamePattern;
};

class SMARTTAGGER_API FSmartTaggerModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void OnOpenQuickTagger() const;

private:
	void RegisterMenus();

	mutable TWeakPtr<SWindow> TaggerWindow;
	TSharedPtr<FUICommandList> PluginCommands;
	FDelegateHandle RegisterMenuCallback;
};
