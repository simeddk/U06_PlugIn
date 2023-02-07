#include "MeshViewer_Viewport_Client.h"
#include "MeshViewer_Viewport.h"

FMeshViewer_Viewport_Client::FMeshViewer_Viewport_Client(FPreviewScene* InScene, const TSharedRef<SMeshViewer_Viewport>& InViewport)
	: FEditorViewportClient(nullptr, InScene, StaticCastSharedRef<SMeshViewer_Viewport>(InViewport))
{
	SetViewMode(EViewModeIndex::VMI_Lit);

	SetViewRotation(FRotator(-40, -90, 0));
	SetViewLocationForOrbiting(FVector(0, 0, 75), 1000);
}
