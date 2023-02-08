#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAsset.generated.h"

UCLASS()
class TOY_API UCAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		float DropRate;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
		class UMaterialInstanceConstant* Material;
	
};
