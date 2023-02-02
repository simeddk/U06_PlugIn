#include "MeshActor_DetailPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FMeshActor_DetailPanel::MakeInstance()
{
	return MakeShareable(new FMeshActor_DetailPanel());
}

void FMeshActor_DetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& cateory = DetailBuilder.EditCategory("Awesome Category");

	cateory.AddCustomRow(FText::FromString("Awesome Category"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Material Instance"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FMeshActor_DetailPanel::OnClicked_ShuffleMaterial)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];

	DetailBuilder.GetObjectsBeingCustomized(Objects);

}

FReply FMeshActor_DetailPanel::OnClicked_ShuffleMaterial()
{
	GLog->Log(Objects[0]->GetName());
	return FReply::Handled();
}
