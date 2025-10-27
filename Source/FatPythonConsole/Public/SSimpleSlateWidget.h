#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STextBlock;

class SSimpleSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSimpleSlateWidget) {}
		SLATE_ARGUMENT(FText, InitialText)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnButtonClicked();

private:
	int32 Counter;
	TSharedPtr<STextBlock> TextBlock;
};