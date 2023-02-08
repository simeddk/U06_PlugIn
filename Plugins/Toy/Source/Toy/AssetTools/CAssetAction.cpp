#include "CAssetAction.h"
#include "CAsset.h"

CAssetAction::CAssetAction(EAssetTypeCategories::Type InCategory)
	: Category(InCategory)
{
}

CAssetAction::~CAssetAction()
{
}

FText CAssetAction::GetName() const
{
	return FText::FromString("Awesome Asset");
}

UClass* CAssetAction::GetSupportedClass() const
{
	return UCAsset::StaticClass();
}

FColor CAssetAction::GetTypeColor() const
{
	return FColor::Black;
}

uint32 CAssetAction::GetCategories()
{
	return Category;
}
