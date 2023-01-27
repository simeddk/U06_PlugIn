#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyle> FIconStyle::Instance = nullptr;

TSharedPtr<FIconStyle> FIconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyle());

	return Instance;
}

void FIconStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path /=  "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("ToolBarIcon", path / "Icon.png", FVector2D(48), ToolBar_Icon);
	RegisterIcon("ToolBarIcon2", path / "Icon2.png", FVector2D(48), ToolBar_Icon2);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FIconStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InSize);

	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);

	OutIcon = FSlateIcon(StyleSetName, FName(name));
}

FIconStyle::~FIconStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);

	if (StyleSet.IsValid())
		StyleSet.Reset();
}
