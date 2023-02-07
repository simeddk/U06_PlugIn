#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMeshObject.generated.h"

UCLASS()
class GAME_API UCMeshObject : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FVector Location;
	
};
