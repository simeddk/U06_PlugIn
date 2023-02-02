#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FMeshActor_DetailPanel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ShuffleMaterial();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
