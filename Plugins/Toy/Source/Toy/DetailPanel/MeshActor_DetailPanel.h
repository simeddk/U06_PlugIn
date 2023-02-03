#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FBinaryData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	//Todo
	friend FArchive& operator <<(FArchive& InArchive, FBinaryData& InData)
	{
		return InArchive;
	}
};

class TOY_API FMeshActor_DetailPanel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveMesh();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
