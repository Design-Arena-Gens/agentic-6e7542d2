#include "SmartTagger.h"

#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "ScopedTransaction.h"
#include "Selection.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "FSmartTaggerPanel"

void SSmartTaggerPanel::Construct(const FArguments& InArgs)
{
	TagString = TEXT("Gameplay.Default");
	MetadataKey = TEXT("Category");
	MetadataValue = TEXT("Prop");
	RenamePattern = TEXT("{BaseName}_Tagged_{Index}");

	ChildSlot
	[
		SNew(SBorder)
		.Padding(16.f)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 12.f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Description", "Apply gameplay tags and metadata to every selected actor in the level. Each entry is comma separated."))
					.WrapTextAt(460.f)
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 8.f)
				[
					SNew(STextBlock).Text(LOCTEXT("TagLabel", "Gameplay Tags (comma separated)"))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 12.f)
				[
					SNew(SEditableTextBox)
					.Text_Lambda([this]() { return FText::FromString(TagString); })
					.OnTextCommitted_Lambda([this](const FText& InText, ETextCommit::Type) { TagString = InText.ToString(); })
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 8.f)
				[
					SNew(SCheckBox)
					.IsChecked_Lambda([this]() { return bAppend ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
					.OnCheckStateChanged_Lambda([this](ECheckBoxState State) { bAppend = State == ECheckBoxState::Checked; })
					[
						SNew(STextBlock).Text(LOCTEXT("AppendTags", "Append tags instead of replacing"))
					]
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 16.f, 0.f, 8.f)
				[
					SNew(STextBlock).Text(LOCTEXT("MetadataKeyLabel", "Metadata Key"))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 12.f)
				[
					SNew(SEditableTextBox)
					.Text_Lambda([this]() { return FText::FromString(MetadataKey); })
					.OnTextCommitted_Lambda([this](const FText& InText, ETextCommit::Type) { MetadataKey = InText.ToString(); })
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 8.f)
				[
					SNew(STextBlock).Text(LOCTEXT("MetadataValueLabel", "Metadata Value"))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 12.f)
				[
					SNew(SEditableTextBox)
					.Text_Lambda([this]() { return FText::FromString(MetadataValue); })
					.OnTextCommitted_Lambda([this](const FText& InText, ETextCommit::Type) { MetadataValue = InText.ToString(); })
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 16.f, 0.f, 8.f)
				[
					SNew(STextBlock).Text(LOCTEXT("RenamePatternLabel", "Rename Pattern ({Index} will be replaced by a running number)"))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 12.f)
				[
					SNew(SEditableTextBox)
					.Text_Lambda([this]() { return FText::FromString(RenamePattern); })
					.OnTextCommitted_Lambda([this](const FText& InText, ETextCommit::Type) { RenamePattern = InText.ToString(); })
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 12.f, 0.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("ApplyButton", "Apply Tags & Metadata"))
					.OnClicked(this, &SSmartTaggerPanel::OnApplyTagsClicked)
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 12.f, 0.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("RenameButton", "Rename Selected Actors"))
					.OnClicked(this, &SSmartTaggerPanel::OnRenameClicked)
				]
			]
		]
	];
}

FReply SSmartTaggerPanel::OnApplyTagsClicked()
{
#if WITH_EDITOR
	if (!GEditor)
	{
		return FReply::Handled();
	}

	TArray<FString> TagTokens;
	TagString.ParseIntoArray(TagTokens, TEXT(","), true);

	for (FString& Token : TagTokens)
	{
		Token = Token.TrimStartAndEnd();
	}

	TagTokens.RemoveAll([](const FString& Token) { return Token.IsEmpty(); });

	const FScopedTransaction Transaction(LOCTEXT("ApplyTagsTransaction", "Apply Smart Tagger Tags"));

	USelection* SelectedActors = GEditor->GetSelectedActors();
	if (!SelectedActors)
	{
		return FReply::Handled();
	}

	int32 Index = 1;
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		if (AActor* Actor = Cast<AActor>(*It))
		{
			Actor->Modify();

			if (!bAppend)
			{
				Actor->Tags.Empty();
			}

			for (const FString& Token : TagTokens)
			{
				Actor->Tags.AddUnique(FName(Token));
			}

			if (!MetadataKey.IsEmpty() && !MetadataValue.IsEmpty())
			{
				const FString MetadataEntry = FString::Printf(TEXT("%s:%s"), *MetadataKey, *MetadataValue);
				Actor->Tags.AddUnique(FName(*MetadataEntry));
			}

			if (!RenamePattern.IsEmpty())
			{
				const FString BaseName = Actor->GetActorLabel(false);
				FString NewName = RenamePattern;
				NewName = NewName.Replace(TEXT("{Index}"), *FString::FromInt(Index));
				NewName = NewName.Replace(TEXT("{BaseName}"), *BaseName);
				GEditor->SetActorLabelUnique(Actor, NewName);
			}

			++Index;
		}
	}
#endif

	return FReply::Handled();
}

FReply SSmartTaggerPanel::OnRenameClicked()
{
#if WITH_EDITOR
	if (!GEditor || RenamePattern.IsEmpty())
	{
		return FReply::Handled();
	}

	const FScopedTransaction Transaction(LOCTEXT("RenameActorsTransaction", "Rename Selected Actors"));

	USelection* SelectedActors = GEditor->GetSelectedActors();
	if (!SelectedActors)
	{
		return FReply::Handled();
	}

	int32 Index = 1;
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		if (AActor* Actor = Cast<AActor>(*It))
		{
			Actor->Modify();

			const FString BaseName = Actor->GetActorLabel(false);
			FString NewName = RenamePattern;
			NewName = NewName.Replace(TEXT("{Index}"), *FString::FromInt(Index));
			NewName = NewName.Replace(TEXT("{BaseName}"), *BaseName);
			GEditor->SetActorLabelUnique(Actor, NewName);
			++Index;
		}
	}
#endif

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
