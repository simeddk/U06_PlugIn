#include "CVertexMesh.h"
#include "ProceduralMeshComponent.h"

ACVertexMesh::ACVertexMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh");
	RootComponent = ProcMesh;

	//Define Vertex Desc

	//DC->Draw
}

void ACVertexMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACVertexMesh::AddIndices(int32 InStart)
{
}

