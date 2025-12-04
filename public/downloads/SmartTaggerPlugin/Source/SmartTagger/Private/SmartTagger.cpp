#include "SmartTagger.h"

#include "LevelEditor.h"
#include "SmartTaggerStyle.h"
#include "SmartTaggerCommands.h"
#include "ToolMenus.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"

#define LOCTEXT_NAMESPACE "FSmartTaggerModule"

void FSmartTaggerModule::StartupModule()
{
	SmartTaggerStyle::Initialize();
	SmartTaggerStyle::ReloadTextures();

	FSmartTaggerCommands::Register();

	PluginCommands = MakeShared<FUICommandList>();
	PluginCommands->MapAction(
		FSmartTaggerCommands::Get().ExecuteQuickTagger,
		FExecuteAction::CreateRaw(this, &FSmartTaggerModule::OnOpenQuickTagger));

	if (UToolMenus::IsToolMenuUIEnabled())
	{
		RegisterMenuCallback = UToolMenus::RegisterStartupCallback(
			FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSmartTaggerModule::RegisterMenus));
	}
}

void FSmartTaggerModule::ShutdownModule()
{
	UToolMenus::UnregisterOwner(this);
	if (RegisterMenuCallback.IsValid())
	{
		UToolMenus::UnRegisterStartupCallback(RegisterMenuCallback);
		RegisterMenuCallback.Reset();
	}
	FSmartTaggerCommands::Unregister();
	SmartTaggerStyle::Shutdown();
}

void FSmartTaggerModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	FToolMenuSection& Section = Menu->AddSection("SmartTagger", LOCTEXT("SectionName", "Smart Tagger"));

	FToolMenuEntry Entry = FToolMenuEntry::InitToolBarButton(
		FSmartTaggerCommands::Get().ExecuteQuickTagger,
		LOCTEXT("QuickTaggerLabel", "Smart Tagger"),
		LOCTEXT("QuickTaggerTooltip", "Open the Smart Tagger window to mass-update tags on selected actors."),
		FSlateIcon(SmartTaggerStyle::GetStyleSetName(), "SmartTagger.Icon"));

	Entry.SetCommandList(PluginCommands);
	Section.AddEntry(Entry);
}

void FSmartTaggerModule::OnOpenQuickTagger() const
{
#if WITH_EDITOR
	if (!TaggerWindow.IsValid())
	{
		TSharedRef<SWindow> Window = SNew(SWindow)
			.Title(LOCTEXT("TaggerWindowTitle", "Smart Tagger"))
			.ClientSize(FVector2D(520.f, 420.f))
			.SupportsMinimize(false)
			.SupportsMaximize(false);

		Window->SetContent(SNew(SSmartTaggerPanel));
		TaggerWindow = Window;
		FSlateApplication::Get().AddWindow(Window);
	}
	else
	{
		TaggerWindow->BringToFront();
	}
#endif
}

IMPLEMENT_MODULE(FSmartTaggerModule, SmartTagger)

#undef LOCTEXT_NAMESPACE
