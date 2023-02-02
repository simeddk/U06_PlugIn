#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMeshActor.generated.h"

UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	Brick, Gold, Rock, Rubber, Max
};

USTRUCT(BlueprintType)
struct FMaterialParameterData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)	class UTexture* BaseMap;
	UPROPERTY(EditAnywhere)	class UTexture* RoughnessMap;
	UPROPERTY(EditAnywhere)	class UTexture* NormalMap;
	UPROPERTY(EditAnywhere) float Metallic;
	UPROPERTY(EditAnywhere) float Roughness_Min;
	UPROPERTY(EditAnywhere) float Roughness_Max;
};

UCLASS()
class GAME_API ACMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMeshActor();

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
public:
	void ShuffleMaterial();
#endif

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;

	UPROPERTY(EditDefaultsOnly)
		FMaterialParameterData MaterialParameters[(int32)EMaterialType::Max];
};
