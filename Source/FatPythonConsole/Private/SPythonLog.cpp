#include "SPythonLog.h"
#include "Framework/Text/SlateTextLayout.h"
#include "SlateBasics.h"


//
// FPythonLogTextLayoutMarshaller
//

TSharedRef<FPythonLogTextLayoutMarshaller> FPythonLogTextLayoutMarshaller::Create(TArray<TSharedPtr<FLogMessage>> InMessages)
{
	return MakeShareable(new FPythonLogTextLayoutMarshaller(MoveTemp(InMessages)));
}

FPythonLogTextLayoutMarshaller::FPythonLogTextLayoutMarshaller(TArray< TSharedPtr<FLogMessage> > InMessages)
	: Messages(MoveTemp(InMessages)), TextLayout(nullptr)
{
}

FPythonLogTextLayoutMarshaller::~FPythonLogTextLayoutMarshaller()
{
}

void FPythonLogTextLayoutMarshaller::SetText(const FString& SourceString, FTextLayout& TargetTextLayout)
{
	TextLayout = &TargetTextLayout;
	AppendMessagesToTextLayout(Messages);
}

void FPythonLogTextLayoutMarshaller::GetText(FString& TargetString, const FTextLayout& SourceTextLayout)
{
	SourceTextLayout.GetAsText(TargetString);
}

bool FPythonLogTextLayoutMarshaller::AppendMessage(const TCHAR* InText, const ELogVerbosity::Type InVerbosity, const FName& InCategory)
{
	TArray<TSharedPtr<FLogMessage>> NewMessages;
	if (!SPythonLog::CreateLogMessages(InText, InVerbosity, InCategory, NewMessages))
		return false;

	const bool bWasEmpty = Messages.Num() == 0;
	Messages.Append(NewMessages);

	if (TextLayout)
	{
		if (bWasEmpty)
		{
			TextLayout->ClearLines();
		}

		AppendMessagesToTextLayout(NewMessages);
	}
	else
	{
		MakeDirty();
	}

	return true;
}

void FPythonLogTextLayoutMarshaller::AppendMessagesToTextLayout(const TArray<TSharedPtr<FLogMessage>>& InMessages)
{
	TArray<FTextLayout::FNewLineData> LinesToAdd;
	LinesToAdd.Reserve(InMessages.Num());

	for (const auto& CurrentMessage : InMessages)
	{
		const FTextBlockStyle& MessageTextStyle = FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>(CurrentMessage->Style);

		TSharedRef<FString> LineText = CurrentMessage->Message;

		TArray<TSharedRef<IRun>> Runs;
		Runs.Add(FSlateTextRun::Create(FRunInfo(), LineText, MessageTextStyle));
		
		LinesToAdd.Emplace(MoveTemp(LineText), MoveTemp(Runs));
	}

	TextLayout->AddLines(LinesToAdd);
}

void FPythonLogTextLayoutMarshaller::ClearMessages()
{
	Messages.Empty();
	MakeDirty();
}

int32 FPythonLogTextLayoutMarshaller::GetNumMessages() const
{
	return Messages.Num();
}


//
// SPythonLog
//

bool SPythonLog::CreateLogMessages(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category, TArray<TSharedPtr<FLogMessage>>& OutMessages)
{
	// Skip color events
	if (Verbosity == ELogVerbosity::SetColor)
		return false;

	FName Style;
	if (Category == NAME_Cmd)
	{
		Style = FName(TEXT("Log.Command"));
	}
	else if (Verbosity == ELogVerbosity::Error)
	{
		Style = FName(TEXT("Log.Error"));
	}
	else if (Verbosity == ELogVerbosity::Warning)
	{
		Style = FName(TEXT("Log.Warning"));
	}
	else
	{
		Style = FName(TEXT("Log.Normal"));
	}

	const int32 OldNumMessages = OutMessages.Num();

	// handle multiline strings by breaking them apart by line
	TArray<FTextRange> LineRanges;
	FString CurrentLogDump = V;
	FTextRange::CalculateLineRangesFromString(CurrentLogDump, LineRanges);
	
	for (const FTextRange& LineRange : LineRanges)
	{
		if (LineRange.IsEmpty())
			continue;

		FString Line = CurrentLogDump.Mid(LineRange.BeginIndex, LineRange.Len());
		Line = Line.ConvertTabsToSpaces(4);

		OutMessages.Add(MakeShareable(new FLogMessage(MakeShareable(new FString(Line)))));
	}

	return OldNumMessages != OutMessages.Num();
}


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPythonLog::Construct(const FArguments& InArgs)
{
	MessagesTextBox = SNew(SMultiLineEditableTextBox)
		.Style(FAppStyle::Get(), "Log.TextBox")
		.ForegroundColor(FLinearColor::Gray)
		.Marshaller(MessagesTextMarshaller)
		.IsReadOnly(true)
		.AlwaysShowScrollbars(true)
		//.OnVScrollBarUserScrolled(this, &SPythonLog::OnUserScrolled)
		//.ContextMenuExtender(this, &SPythonLog::ExtendTextBoxMenu)
		;

	ChildSlot
	[
		SNew(SVerticalBox)

		// Console output and filters
		+ SVerticalBox::Slot()
		[
			SNew(SBorder)
			.Padding(3)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)

				// Output log area
				+ SVerticalBox::Slot()
				.FillHeight(1)
				[
					MessagesTextBox.ToSharedRef()
				]
			]
		]

		// Console input box
		// TODO
	];

	GLog->AddOutputDevice(this);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

SPythonLog::~SPythonLog()
{
	if (GLog != NULL)
	{
		GLog->RemoveOutputDevice(this);
	}
}

void SPythonLog::Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category)
{
	
}
