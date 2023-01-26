#include "Toy.h"
#include "Toolbar/ButtonCommand.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	FButtonCommand::Register();

	FToolBarExtensionDelegate toolBarBuilderDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar);

	Extender = MakeShareable(new FExtender());
	Extender->AddToolBarExtension("Complie", EExtensionHook::Before, nullptr, toolBarBuilderDelegate);

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FToyModule::ShutdownModule()
{
}

void FToyModule::AddToolBar(class FToolBarBuilder& InBuilder)
{
	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //Todo. ??�o��?

	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().ID,
		NAME_None,
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data"),
		icon
	);

	//��ư�� ����(��ư�� ������, ��ư ������ �� �׼�..)
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)