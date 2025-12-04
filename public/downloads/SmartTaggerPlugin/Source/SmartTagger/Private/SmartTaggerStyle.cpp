#include "SmartTaggerStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "Brushes/SlateVectorImageBrush.h"
#include "Framework/Application/SlateApplication.h"

TSharedPtr<FSlateStyleSet> FSmartTaggerStyle::StyleInstance = nullptr;

void FSmartTaggerStyle::Initialize()
{
	if (StyleInstance.IsValid())
	{
		return;
	}

	StyleInstance = Create();
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FSmartTaggerStyle::Shutdown()
{
	if (!StyleInstance.IsValid())
	{
		return;
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	StyleInstance.Reset();
}

TSharedRef<FSlateStyleSet> FSmartTaggerStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShared<FSlateStyleSet>("SmartTaggerStyle");

	FString PluginBaseDir;
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("SmartTagger")))
	{
		PluginBaseDir = Plugin->GetBaseDir();
	}
	else
	{
		PluginBaseDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("SmartTagger"));
	}

	const FVector2D Icon40x40(40.f, 40.f);
	Style->Set("SmartTagger.Icon", new FSlateVectorImageBrush(PluginBaseDir / TEXT("Resources/Icon.svg"), Icon40x40));

	return Style;
}

void FSmartTaggerStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FSmartTaggerStyle::Get()
{
	return *StyleInstance;
}

FName FSmartTaggerStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SmartTaggerStyle"));
	return StyleSetName;
}
