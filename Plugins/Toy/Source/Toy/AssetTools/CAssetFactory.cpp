#include "CAssetFactory.h"
#include "CAsset.h"

UCAssetFactory::UCAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UCAsset::StaticClass();
}

UObject* UCAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UCAsset>(InParent, InName, Flags);
}
