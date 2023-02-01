#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

UCLASS()
class AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGamePlayerController();

	FORCEINLINE void SetCursorLocation(const FVector& InLocation) { CursorLocation = InLocation; }

protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void MoveToMouseCursor();

	void SetNewMoveDestination(const FVector DestLocation);

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void OnSlice();

private:
	FVector CursorLocation;
};


