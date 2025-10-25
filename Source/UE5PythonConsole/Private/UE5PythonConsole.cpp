// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5PythonConsole.h"
#include "SSimpleSlateWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Application/SlateApplication.h"

#define LOCTEXT_NAMESPACE "FUE5PythonConsoleModule"

namespace UE5PythonConsole
{
	static const FName PythonLogTabName(TEXT("PythonLog"));
}

TSharedRef<SDockTab> SpawnPythonLog(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab);
		//.Icon(FAppStyle::GetBrush("Log.TabIcon"));
}

void FUE5PythonConsoleModule::StartupModule()
{
	//FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UE5PythonConsole::PythonLogTabName,
	//	);
	//FOnSpawnTab::CreateStatic(
	
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FUE5PythonConsoleModule::CreatePluginWindow);
}

void FUE5PythonConsoleModule::ShutdownModule()
{
	if (PluginWindow.IsValid())
	{
		PluginWindow->RequestDestroyWindow();
	}
}

void FUE5PythonConsoleModule::CreatePluginWindow()
{
	PluginWindow = SNew(SWindow)
		.Title(FText::FromString(TEXT("Simple Slate Widget")))
		.ClientSize(FVector2D(400,200))
		.SizingRule(ESizingRule::UserSized)
		.AutoCenter(EAutoCenter::PreferredWorkArea)
		.SupportsMinimize(false)
		.SupportsMaximize(false);

	PluginWindow->SetContent(SNew(SSimpleSlateWidget));

	FSlateApplication::Get().AddWindow(PluginWindow.ToSharedRef());

	PluginWindow->SetOnWindowClosed(FOnWindowClosed::CreateRaw(this, &FUE5PythonConsoleModule::OnWindowClosed));
}

void FUE5PythonConsoleModule::OnWindowClosed(const TSharedRef<SWindow>& Window)
{
	PluginWindow.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE5PythonConsoleModule, UE5PythonConsole)
