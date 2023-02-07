#include "ButtonCommand.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "Serialization/BufferArchive.h"
#include "DetailPanel/MeshActor_DetailPanel.h"
#include "Viewer/MeshViewer.h"
#include "LevelEditorViewport.h"
#include "Objects/CMeshActor_Copied.h"
#include "Objects/CMeshObject.h"
#include "Misc/FileHelper.h"

#define COPIED_CSV

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
	//Open File Dialog
	FString path;

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	TArray<FString> fileNames;
	platform->OpenFileDialog(handle, "Open Mesh to Binanry", path, "", "Binary Files(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
	if (fileNames.Num() < 1) return;

	//File Data To Memory
	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);
	FMemoryReader reader = FMemoryReader(buffer, true);
	buffer.Seek(0);

	//File Data to Struct Data
	FBinaryData data;
	reader << data;
	reader.FlushCache();
	reader.Close();
	GLog->Logf(L"Vertex Count : %d", data.Positions.Num());
	GLog->Logf(L"Iindex Count : %d", data.Indices.Num());

#ifndef COPIED_CSV
	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ",");
		text.Append(data.Normals[i].ToString() + ",");
		text.Append(data.UVs[i].ToString() + ",");
		text.Append(data.Colors[i].ToString() + "\n");
	}

	FString csvFileName = FPaths::GetBaseFilename(fileNames[0], false);
	FString csvSaveName = csvFileName + "_copied.csv";
	FFileHelper::SaveStringToFile(text, *csvSaveName);

	FString str = "";
	str.Append(FPaths::GetCleanFilename(csvSaveName));
	str.Append(" CSV File Saved.");
	GLog->Log(str);
#endif

	FLevelEditorViewportClient* client = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();

	FHitResult hitResult;
	FVector start = client->GetViewLocation();
	FVector end = start + client->GetViewRotation().RotateVector(FVector(10000, 0, 0));
	UWorld* world = GEditor->GetEditorWorldContext().World();
	
	world->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility);
	if (hitResult.bBlockingHit == false) return;

	FTransform transform;
	
	FVector direction = hitResult.TraceEnd - hitResult.TraceStart;
	direction.Normalize();

	FVector location = hitResult.TraceStart + (direction * hitResult.Distance);
	transform.SetLocation(location);

	FRotator rotation = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation(FQuat(rotation));

	ACMeshActor_Copied* actor = world->SpawnActorDeferred<ACMeshActor_Copied>
	(
		ACMeshActor_Copied::StaticClass(),
		transform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	actor->SetPositions(data.Positions);
	actor->SetIndices(data.Indices);
	actor->SetNormals(data.Normals);
	actor->SetUVs(data.UVs);
	actor->SetColors(data.Colors);

	actor->FinishSpawning(transform);
}

void FButtonCommand::OnClick2()
{
	FMeshViewer::OpenWindow(NewObject<UCMeshObject>());
}