#pragma once

#include "CoreMinimal.h"

class TOY_API FIconStyle
{
public:
	static TSharedPtr<FIconStyle> Get();
	static void Shutdown();

private:
	static TSharedPtr<FIconStyle> Instance;

public:
	FIconStyle();
	~FIconStyle();

private:
	void RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutIcon);

private:
	const FName StyleSetName = "ToyStyle";
	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	FSlateIcon ToolBar_Icon;
	FSlateIcon ToolBar_Icon2;
};
