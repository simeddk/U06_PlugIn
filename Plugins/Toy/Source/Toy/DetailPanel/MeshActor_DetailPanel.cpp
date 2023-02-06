#include "MeshActor_DetailPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Objects/CMeshActor.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"

TSharedRef<IDetailCustomization> FMeshActor_DetailPanel::MakeInstance()
{
	return MakeShareable(new FMeshActor_DetailPanel());
}

void FMeshActor_DetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& cateory = DetailBuilder.EditCategory("Awesome Category");

	//Shuffle Material
	cateory.AddCustomRow(FText::FromString("Shuffle"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Material Instance"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FMeshActor_DetailPanel::OnClicked_ShuffleMaterial)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];

	//Save Mesh
	cateory.AddCustomRow(FText::FromString("Save"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Save Mesh"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FMeshActor_DetailPanel::OnClicked_SaveMesh)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Save To Binary File"))
		]
	];

	DetailBuilder.GetObjectsBeingCustomized(Objects);

}

FReply FMeshActor_DetailPanel::OnClicked_ShuffleMaterial()
{
	ACMeshActor* actor = Cast<ACMeshActor>(Objects[0]);
	if (actor == nullptr) return FReply::Unhandled();
	actor->ShuffleMaterial();

	return FReply::Handled();
}

FReply FMeshActor_DetailPanel::OnClicked_SaveMesh()
{
	//Get StaticMesh Asset
	ACMeshActor* actor = Cast<ACMeshActor>(Objects[0]);
	UStaticMeshComponent* comp = Cast<UStaticMeshComponent>(actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	UStaticMesh* meshAsset = comp->GetStaticMesh();
	if (meshAsset == nullptr) return FReply::Unhandled();

	//Get LOD Data
	FStaticMeshRenderData* renderData = meshAsset->RenderData.Get();
	FStaticMeshLODResources& lod = renderData->LODResources[0];

	//Get Vertex Data
	FPositionVertexBuffer& vb = lod.VertexBuffers.PositionVertexBuffer; //position
	FStaticMeshVertexBuffer& meshVb = lod.VertexBuffers.StaticMeshVertexBuffer; //uv, normal, tangent
	FColorVertexBuffer& colorVb = lod.VertexBuffers.ColorVertexBuffer; //color
	FRawStaticIndexBuffer& ib = lod.IndexBuffer; //index

	if (vb.GetNumVertices() < 1) return FReply::Unhandled();
	if (ib.GetNumIndices() < 1) return FReply::Unhandled();

	uint32 vertexCount = vb.GetNumVertices();
	int32 indexCount = ib.GetNumIndices();

	GLog->Logf(TEXT("Vertex Count : %d"), vertexCount);
	GLog->Logf(TEXT("Index Count : %d"), indexCount);

	//Save File Dialog
	FString path;

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	TArray<FString> fileNames;
	platform->SaveFileDialog(handle, "Save Mesh to Binanry", path, "", "Binary Files(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
	if (fileNames.Num() < 1) return FReply::Unhandled();

	//Save Binary Data
	FBinaryData data;

	TArray<FColor> colors;
	colorVb.GetVertexColors(colors);
	if (colors.Num() < 1)
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor::White);
	}

	for (uint32 i = 0; i < vertexCount; i++)
	{
		data.Positions.Add(vb.VertexPosition(i));
		data.Normals.Add(meshVb.VertexTangentZ(i));
		data.UVs.Add(meshVb.GetVertexUV(i, 0));
		data.Colors.Add(colors[i]);
	}

	TArray<uint32> indices;
	ib.GetCopy(indices);
	data.Indices.Insert((int32*)indices.GetData(), indexCount, 0);

	//Save Binary File
	FBufferArchive buffer;
	buffer << data;
	
	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
	buffer.FlushCache();
	buffer.Empty();

	FString str;
	str.Append(FPaths::GetCleanFilename(fileNames[0]));
	str.Append(" Binary File Saved.");
	GLog->Log(str);

	//Save CSV File(Debug)
	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ",");
		text.Append(data.Normals[i].ToString() + ",");
		text.Append(data.UVs[i].ToString() + ",");
		text.Append(data.Colors[i].ToString() + "\n");
	}

	FString csvFileName = FPaths::GetBaseFilename(fileNames[0], false);
	FString csvSaveName = csvFileName + ".csv";
	FFileHelper::SaveStringToFile(text, *csvSaveName);

	str = "";
	str.Append(FPaths::GetCleanFilename(csvSaveName));
	str.Append(" CSV File Saved.");
	GLog->Log(str);

	return FReply::Handled();
}