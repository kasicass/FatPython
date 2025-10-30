#include "SPythonLog.h"



//
// SPythonLog
//

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPythonLog::Construct(const FArguments& InArgs)
{
	MessagesTextBox = SNew(SMultiLineEditableTextBox)
		.Style(FAppStyle::Get(), "Log.TextBox")
		.ForegroundColor(FLinearColor::Gray)
		//.Marshaller(MessagesTextMarshaller)
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
