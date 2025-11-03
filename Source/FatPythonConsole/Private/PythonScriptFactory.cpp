#include "PythonScriptFactory.h"
#include "PythonScript.h"

UPythonScriptFactory::UPythonScriptFactory(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	Formats.Add("py;Python Script");

	bCreateNew = false;
	bEditAfterNew = true;

	bEditorImport = true;

	SupportedClass = UPythonScript::StaticClass();
}

UObject* UPythonScriptFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UPythonScript *NewAsset = NewObject<UPythonScript>(InParent, InClass, InName, Flags);
	NewAsset->ScriptPath = Filename;

	bOutOperationCanceled = false;
	return NewAsset;
}
