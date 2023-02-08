#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class TOY_API CAssetAction : public FAssetTypeActions_Base
{
public:
	CAssetAction(EAssetTypeCategories::Type InCategory);
	~CAssetAction();

public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type Category;
};
