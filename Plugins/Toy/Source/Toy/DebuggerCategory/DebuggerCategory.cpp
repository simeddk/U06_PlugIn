#include "DebuggerCategory.h"
#include "GameFramework/Character.h"
#include "CanvasItem.h"
#include "GameFramework/PlayerController.h"

FDebuggerCategory::FDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;
}

FDebuggerCategory::~FDebuggerCategory()
{
}

void FDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	ACharacter* player = Cast<ACharacter>(OwnerPC->GetPawn());
	//PlayerPawn
	{
		PlayerPawnData.Name = player->GetName();
		PlayerPawnData.Location = player->GetActorLocation();
		PlayerPawnData.Forward = player->GetActorForwardVector();
	}

	//ForwardActor
	{
		FHitResult hitResult;
		FVector start = player->GetActorLocation();
		FVector end = start + player->GetActorForwardVector() * 1e+4f;
		
		FCollisionQueryParams parmas;
		parmas.AddIgnoredActor(player);

		player->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, parmas);

		if (hitResult.bBlockingHit)
		{
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}
		else
		{
			ForwardActorData.Name = "";
			ForwardActorData.Location = FVector::ZeroVector;
			ForwardActorData.Forward = FVector::ZeroVector;
		}
		
	}

	//DebuggerActor
	{
		if (!!DebugActor)
		{
			DebuggerActorData.Name = DebugActor->GetName();
			DebuggerActorData.Location = DebugActor->GetActorLocation();
			DebuggerActorData.Forward = DebugActor->GetActorForwardVector();
		}
		else
		{
			DebuggerActorData.Name = "";
			DebuggerActorData.Location = FVector::ZeroVector;
			DebuggerActorData.Forward = FVector::ZeroVector;
		}
	}
}

void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FCanvasTileItem item(FVector2D(10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.5f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, L"  -- Player Pawn -- ");
	CanvasContext.Printf(FColor::White, L"Name : %s", *PlayerPawnData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *PlayerPawnData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *PlayerPawnData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"  -- Forward Actor -- ");
	CanvasContext.Printf(FColor::White, L"Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"  -- Debugger Actor -- ");
	CanvasContext.Printf(FColor::White, L"Name : %s", *DebuggerActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *DebuggerActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *DebuggerActorData.Forward.ToString());
}

TSharedRef<FGameplayDebuggerCategory> FDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FDebuggerCategory());
}
