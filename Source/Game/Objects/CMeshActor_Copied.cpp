#include "CMeshActor_Copied.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACMeshActor_Copied::ACMeshActor_Copied()
{
	bRunConstructionScriptOnDrag = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh");
	RootComponent = ProcMesh;
}

void ACMeshActor_Copied::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ProcMesh->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(), true);

	Material = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Materials/MAT_Write.MAT_Write'")));
	ProcMesh->SetMaterial(0, Material);
}

void ACMeshActor_Copied::BeginPlay()
{
	Super::BeginPlay();
	
}

