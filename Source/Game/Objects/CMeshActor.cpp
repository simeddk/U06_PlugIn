#include "CMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/KismetMathLibrary.h"

ACMeshActor::ACMeshActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Engine/EditorMeshes/Camera/SM_CineCam.SM_CineCam'"));
	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> materialAsset(TEXT("MaterialInstanceConstant'/Game/Materials/MAT_Write.MAT_Write'"));
	if (materialAsset.Succeeded())
		Mesh->SetMaterial(0, materialAsset.Object);
}

void ACMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

#if WITH_EDITOR
void ACMeshActor::ShuffleMaterial()
{
	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, (int32)EMaterialType::Max - 1);

	for (const FTextureParameterValue& value : Material->TextureParameterValues)
	{
		//Todo
		/*if (value.ParameterInfo.Name.Compare("Metallic") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[index].Metallic);

		if (value.ParameterInfo.Name.Compare("Roughness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[index].Roughness_Min);

		if (value.ParameterInfo.Name.Compare("Roughness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[index].Roughness_Max);*/
	}
	
	for (const FScalarParameterValue& value : Material->ScalarParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("Metallic") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[index].Metallic);

		if (value.ParameterInfo.Name.Compare("Roughness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[index].Roughness_Min);

		if (value.ParameterInfo.Name.Compare("Roughness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[index].Roughness_Max);
	}
}
#endif