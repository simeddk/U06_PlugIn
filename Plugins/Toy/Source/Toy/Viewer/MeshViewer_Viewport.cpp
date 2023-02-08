#include "MeshViewer_Viewport.h"
#include "MeshViewer_Viewport_Client.h"
#include "AdvancedPreviewScene.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
}

void SMeshViewer_Viewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(InArgs);


	//FloorMesh
	UStaticMesh* floorMeshAsset = LoadObject<UStaticMesh>(nullptr, L"StaticMesh'/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh'");
	FloorMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient);
	FloorMesh->SetStaticMesh(floorMeshAsset);

	FTransform transform;
	Scene->AddComponent(FloorMesh, transform);

	//Mesh
	UStaticMesh* meshAsset = LoadObject<UStaticMesh>(nullptr, L"StaticMesh'/Engine/EngineMeshes/SM_MatPreviewMesh_01.SM_MatPreviewMesh_01'");
	Mesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient);
	Mesh->SetStaticMesh(meshAsset);

	transform.SetLocation(FVector(0, 0, 100));
	Scene->AddComponent(Mesh, transform);
}

TSharedRef<class FAdvancedPreviewScene> SMeshViewer_Viewport::GetScene()
{
	return Scene.ToSharedRef();
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(Mesh);
	Collector.AddReferencedObject(FloorMesh);
}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FMeshViewer_Viewport_Client(Scene.Get(), SharedThis(this)));

	return ViewportClient.ToSharedRef();
}
