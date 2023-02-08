#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TOY_API SMeshViewer_Viewport : public SEditorViewport, public FGCObject
{
public:
	SMeshViewer_Viewport();

	void Construct(const FArguments& InArgs);
	TSharedRef<class FAdvancedPreviewScene> GetScene();

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<class FAdvancedPreviewScene> Scene;
	TSharedPtr<class FMeshViewer_Viewport_Client> ViewportClient;

private:
	class UStaticMeshComponent* Mesh;
	class UStaticMeshComponent* FloorMesh;
};
