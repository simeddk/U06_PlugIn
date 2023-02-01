#include "CVertexMesh.h"
#include "ProceduralMeshComponent.h"

ACVertexMesh::ACVertexMesh()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.f;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh");
	RootComponent = ProcMesh;

	FVector v = FVector(0.5f);

	//Front
	Positions.Add(FVector(-0.5f, -0.5f, -0.5f)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-0.5f, -0.5f, +0.5f)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-0.5f, +0.5f, -0.5f)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-0.5f, +0.5f, +0.5f)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
		Colors.Add(FColor::Red);
	}
	AddIndices(0);

	//Back
	Positions.Add(FVector(+v.X, +v.Y, -v.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+v.X, +v.Y, +v.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+v.X, -v.Y, -v.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+v.X, -v.Y, +v.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(+1, 0, 0));
		Colors.Add(FColor::Green);
	}
	AddIndices(4);


	//Top
	Positions.Add(FVector(-v.X, -v.Y, +v.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+v.X, -v.Y, +v.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-v.X, +v.Y, +v.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+v.X, +v.Y, +v.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, +1));
		Colors.Add(FColor::Blue);
	}
	AddIndices(8);


	//Bottom
	Positions.Add(FVector(-v.X, -v.Y, -v.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-v.X, +v.Y, -v.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+v.X, -v.Y, -v.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+v.X, +v.Y, -v.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, -1));
		Colors.Add(FColor::Cyan);
	}
	AddIndices(12);


	//Left
	Positions.Add(FVector(+v.X, -v.Y, -v.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+v.X, -v.Y, +v.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-v.X, -v.Y, -v.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-v.X, -v.Y, +v.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, -1, 0));
		Colors.Add(FColor::Magenta);
	}
	AddIndices(16);


	//Right
	Positions.Add(FVector(-v.X, +v.Y, -v.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-v.X, +v.Y, +v.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+v.X, +v.Y, -v.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+v.X, +v.Y, +v.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, +1, 0));
		Colors.Add(FColor::Yellow);
	}
	AddIndices(20);
	

	ProcMesh->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetRelativeScale3D(FVector(100));
}

void ACVertexMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for (int32 i = 0; i < Colors.Num() / 4; i++)
	{
		FColor color = FColor::MakeRandomColor();
		color.A = 255.f;

		Colors[i * 4 + 0] = color;
		Colors[i * 4 + 1] = color;
		Colors[i * 4 + 2] = color;
		Colors[i * 4 + 3] = color;
	}

	ProcMesh->UpdateMeshSection(0, Positions, Normals, UVs, Colors, TArray<FProcMeshTangent>());
}

void ACVertexMesh::AddIndices(int32 InStart)
{
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);

	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 2);
}

