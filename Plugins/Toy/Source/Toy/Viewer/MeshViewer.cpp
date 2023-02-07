#include "MeshViewer.h"
#include "MeshViewer_Viewport.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("MeshViewer");
const static FName ViewportTabId = TEXT("Viewport");
const static FName PreviewTabId = TEXT("Preview");
const static FName DetailsTabId = TEXT("Details");

void FMeshViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FMeshViewer());
	Instance->Open(InAsset);
}

void FMeshViewer::ShutDown()
{
	/*if (Instance.IsValid())
		Instance.Reset();*/
}

void FMeshViewer::Open(UObject* InAsset)
{
	Viewport = SNew(SMeshViewer_Viewport);

	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			//MainSplit(措)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.75f)
				//Viewport
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				//DescPanel(吝)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.25f)
					//Preview(家)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabId, ETabState::OpenedTab)
					)//Preview(家)
					//Details(家)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabId, ETabState::OpenedTab)
					)//Details(家)
				)//(吝)
			)//(措)
		
		);


	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), ToolkitName, layout, true, true, InAsset);
}

void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);
	TabManager->RegisterTabSpawner(ViewportTabId, tab);
}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			Viewport.ToSharedRef()
		];
}


FName FMeshViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitName);
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return ToolkitName.ToString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Red;
}