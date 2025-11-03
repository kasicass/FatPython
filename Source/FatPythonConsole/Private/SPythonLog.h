#pragma once

#include "CoreMinimal.h"
#include "Framework/Text/BaseTextLayoutMarshaller.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

struct FLogMessage
{
	TSharedRef<FString> Message;
	FName Style;

	FLogMessage(const TSharedRef<FString>& NewMessage, FName NewStyle = NAME_None)
		: Message(NewMessage), Style(NewStyle)
	{
	}
};

class FPythonLogTextLayoutMarshaller : public FBaseTextLayoutMarshaller
{
public:
	static TSharedRef<FPythonLogTextLayoutMarshaller> Create(TArray<TSharedPtr<FLogMessage>> InMessages);

	virtual ~FPythonLogTextLayoutMarshaller();

	// ITextLayoutMarshaller
	virtual void SetText(const FString& SourceString, FTextLayout& TargetTextLayout) override;
	virtual void GetText(FString& TargetString, const FTextLayout& SourceTextLayout) override;

	bool AppendMessage(const TCHAR* InText, const ELogVerbosity::Type InVerbosity, const FName& InCategory);
	void ClearMessages();

	int32 GetNumMessages() const;

protected:
	FPythonLogTextLayoutMarshaller(TArray< TSharedPtr<FLogMessage> > InMessages);
	
	void AppendMessagesToTextLayout(const TArray<TSharedPtr<FLogMessage>>& InMessages);

private:
	// All log messages show in the text box
	TArray<TSharedPtr<FLogMessage>> Messages;

	// Holds cached numbers of messages to avoid unnecessary re-filtering
	int32 CachedNumMessages;

	// Flag indicating the messages count cache needs rebuilding
	bool bNumMessagesCacheDirty;

	FTextLayout* TextLayout;
};

// Widget which holds a list view of logs of the program output
// as well as a combo box for entering in new commands
class SPythonLog : public SCompoundWidget, public FOutputDevice
{
public:
	static bool CreateLogMessages(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category, TArray< TSharedPtr<FLogMessage> >& OutMessages);
	
public:
	SLATE_BEGIN_ARGS(SPythonLog) {}
		// All messages captured before this log window has been created
		SLATE_ARGUMENT(TArray<TSharedPtr<FLogMessage>>, Messages)
	SLATE_END_ARGS()

	virtual ~SPythonLog();

	void Construct(const FArguments& InArgs);

protected:
	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;

private:
	// Converts the array of messages into something the text box understands
	TSharedPtr<FPythonLogTextLayoutMarshaller> MessagesTextMarshaller;
	
	// The editable text showing all log messages
	TSharedPtr<SMultiLineEditableTextBox> MessagesTextBox;
};
