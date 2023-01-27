#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("LoadMesh", FText::FromString("Load Mesh Data"), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (Command.IsValid())
		Command.Reset();

}


void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(ID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ID2, "OpenViewer", "Open Viewer", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
	
	Command->MapAction(ID, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClick), FCanExecuteAction());
	Command->MapAction(ID2, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClick2), FCanExecuteAction());
}

void FButtonCommand::OnClick()
{
	UE_LOG(LogTemp, Error, TEXT("Load Mesh Button Clicked"));
}

void FButtonCommand::OnClick2()
{
	UE_LOG(LogTemp, Error, TEXT("Open Viewer Button Clicked"));
}