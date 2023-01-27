#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;

private:
	void OnClick();
	void OnClick2();

public:
	TSharedPtr<FUICommandInfo> ID;
	TSharedPtr<FUICommandInfo> ID2;
	TSharedPtr<FUICommandList> Command;
};
