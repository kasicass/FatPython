// Copyright Epic Games, Inc. All Rights Reserved.

#include "FatPythonConsoleModule.h"
#include "SSimpleSlateWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Application/SlateApplication.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FFatPythonConsoleModule"

static const FName FatPythonLogTabName(TEXT("FatPythonLog"));

TSharedRef<SDockTab> SpawnPythonLog(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab);
		//.Icon(FAppStyle::GetBrush("Log.TabIcon"));
}

void FFatPythonConsoleModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FatPythonLogTabName, FOnSpawnTab::CreateStatic(&SpawnPythonLog))
		.SetDisplayName(NSLOCTEXT("UnrealEditor", "PythonLogTab", "Python Console"))
		.SetTooltipText(NSLOCTEXT("UnrealEditor", "PythonLogTooltipText", "Open the Python Console tab."))
		.SetGroup( WorkspaceMenu::GetMenuStructure().GetDeveloperToolsLogCategory() )
		.SetIcon( FSlateIcon(FAppStyle::GetAppStyleSetName(), "Log.TabIcon") );
	
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FFatPythonConsoleModule::CreatePluginWindow);
}

void FFatPythonConsoleModule::ShutdownModule()
{
	if (PluginWindow.IsValid())
	{
		PluginWindow->RequestDestroyWindow();
	}
}

void FFatPythonConsoleModule::CreatePluginWindow()
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

	PluginWindow->SetOnWindowClosed(FOnWindowClosed::CreateRaw(this, &FFatPythonConsoleModule::OnWindowClosed));
}

void FFatPythonConsoleModule::OnWindowClosed(const TSharedRef<SWindow>& Window)
{
	PluginWindow.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFatPythonConsoleModule, FFatPythonConsole)
