#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToyModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddToolBar(class FToolBarBuilder& InBuilder);
	void AddToolBar2(class FToolBarBuilder& InBuilder);

private:
	TSharedPtr<FExtender> Extender;

};
