#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMeshActor_Copied.generated.h"

UCLASS()
class GAME_API ACMeshActor_Copied : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMeshActor_Copied();

	virtual void OnConstruction(const FTransform& Transform) override;

	FORCEINLINE void SetPositions(const TArray<FVector>& InPositions) { Positions = InPositions; }
	FORCEINLINE void SetNormals(const TArray<FVector>& InNormals) { Normals = InNormals; }
	FORCEINLINE void SetColors(const TArray<FColor>& InColors) { Colors = InColors;	}
	FORCEINLINE void SetUVs(const TArray<FVector2D>& InUVs) { UVs = InUVs; }
	FORCEINLINE void SetIndices(const TArray<int32>& InIndices) { Indices = InIndices; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;


private:
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;
};
