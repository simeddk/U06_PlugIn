#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSlicableMesh.generated.h"

UCLASS()
class GAME_API ACSlicableMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSlicableMesh();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;
};
