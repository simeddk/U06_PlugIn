#include "CSlicableMesh.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

ACSlicableMesh::ACSlicableMesh()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Scene);

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh");
	ProcMesh->SetupAttachment(Scene);

	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	if (staticMeshAsset.Succeeded())
		StaticMesh->SetStaticMesh(staticMeshAsset.Object);

	StaticMesh->SetVisibility(false);
	StaticMesh->SetCollisionProfileName("NoCollision");

	ProcMesh->SetSimulatePhysics(true);
	ProcMesh->bUseComplexAsSimpleCollision = false;
}

void ACSlicableMesh::OnConstruction(const FTransform& Transform)
{
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(StaticMesh, 0, ProcMesh, true);
}

void ACSlicableMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

