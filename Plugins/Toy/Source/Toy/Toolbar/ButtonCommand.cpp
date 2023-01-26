#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("LoadMesh", FText::FromString("Load Mesh Data"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

FButtonCommand::~FButtonCommand()
{
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(ID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
}
