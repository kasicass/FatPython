#include "SSimpleSlateWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void SSimpleSlateWidget::Construct(const FArguments& InArgs)
{
	Counter = 0;

	ChildSlot
	[
		SNew(SBorder)
		.Padding(FMargin(20))
		[
			SNew(SVerticalBox)
			
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0,0,0,10))
			[
				SAssignNew(TextBlock, STextBlock)
				.Text(FText::FromString("Counter: 0"))
				.Justification(ETextJustify::Center)
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("Click Me!")))
				.OnClicked(this, &SSimpleSlateWidget::OnButtonClicked)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]
		]
	];
}

FReply SSimpleSlateWidget::OnButtonClicked()
{
	Counter++;
	TextBlock->SetText(FText::FromString(FString::Printf(TEXT("Counter: %i"), Counter)));
	return FReply::Handled();
}
