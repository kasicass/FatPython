// Copyright Epic Games, Inc. All Rights Reserved.

#include "FatPythonConsoleModule.h"
#include "SSimpleSlateWidget.h"
#include "SPythonLog.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Application/SlateApplication.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FFatPythonConsoleModule"

static const FName FatPythonLogTabName = FName(TEXT("FatPythonLog"));

// This class is to capture all log output even if the log window is closed
class FPythonLogHistory : public FOutputDevice
{
public:
	FPythonLogHistory()
	{
		if (GLog)
		{
			GLog->AddOutputDevice(this);
			GLog->SerializeBacklog(this);
		}
	}

	~FPythonLogHistory()
	{
		if (GLog != nullptr)
		{
			GLog->RemoveOutputDevice(this);
		}
	}

	const TArray<TSharedPtr<FLogMessage>>& GetMessages() const
	{
		return Messages;
	}

protected:
	virtual void Serialize( const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category ) override
	{
		SPythonLog::CreateLogMessages(V, Verbosity, Category, Messages);
	}

private:
	TArray<TSharedPtr<FLogMessage>> Messages;
};

static TSharedPtr<FPythonLogHistory> PythonLogHistory = MakeShareable(new FPythonLogHistory());

static TSharedRef<SDockTab> SpawnPythonLog(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(NSLOCTEXT("PythonConsole", "TabTitle", "Python Console"))
		[
			SNew(SPythonLog).Messages(PythonLogHistory->GetMessages())
		];
}

void FFatPythonConsoleModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FatPythonLogTabName, FOnSpawnTab::CreateStatic(&SpawnPythonLog))
		.SetDisplayName(NSLOCTEXT("UnrealEditor", "PythonLogTab", "FatPython Console"))
		.SetTooltipText(NSLOCTEXT("UnrealEditor", "PythonLogTooltipText", "Open the FatPython Console."))
		.SetGroup( WorkspaceMenu::GetMenuStructure().GetDeveloperToolsLogCategory() )
		.SetIcon( FSlateIcon(FAppStyle::GetAppStyleSetName(), "Log.TabIcon") );
	
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FFatPythonConsoleModule::CreatePluginWindow);
}

void FFatPythonConsoleModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FatPythonLogTabName);
	}
	
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
	
IMPLEMENT_MODULE(FFatPythonConsoleModule, FatPythonConsole)
