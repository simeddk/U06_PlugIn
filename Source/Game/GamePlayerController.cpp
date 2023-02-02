#include "GamePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProceduralMeshComponent.h" 
#include "Materials/MaterialInstanceConstant.h"
#include "KismetProceduralMeshLibrary.h"

AGamePlayerController::AGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
		MoveToMouseCursor();
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AGamePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Slice", IE_Pressed, this, &AGamePlayerController::OnSlice);
}

void AGamePlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
		SetNewMoveDestination(Hit.ImpactPoint);
}

void AGamePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AGamePlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void AGamePlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}

void AGamePlayerController::OnSlice()
{
	//LineTrace
	FVector start = GetPawn()->GetActorLocation();
	FVector end = FVector(CursorLocation.X, CursorLocation.Y, start.Z);

	TArray<AActor*> ignores;
	ignores.Add(GetPawn());

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ignores,
		EDrawDebugTrace::ForDuration,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red,
		1.f
	);
	if (hitResult.IsValidBlockingHit() == false) return;

	//Slice
	UProceduralMeshComponent* otherProcMesh = Cast<UProceduralMeshComponent>(hitResult.Component);
	if (otherProcMesh == nullptr) return;

	UMaterialInstanceConstant* material 
		= Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Materials/MAT_Plane_Inst.MAT_Plane_Inst'")));

	UProceduralMeshComponent* outProcMesh = nullptr;

	FVector direction = end - start;
	direction.Normalize();

	FVector planeNormal = GetPawn()->GetActorUpVector() ^ direction;
	planeNormal.Normalize();

	UKismetProceduralMeshLibrary::SliceProceduralMesh
	(
		otherProcMesh,
		hitResult.Location,
		planeNormal,
		true,
		outProcMesh,
		EProcMeshSliceCapOption::CreateNewSectionForCap,
		material
	);

	outProcMesh->SetSimulatePhysics(true);
	outProcMesh->AddImpulse(direction * 600, NAME_None, true);
}

