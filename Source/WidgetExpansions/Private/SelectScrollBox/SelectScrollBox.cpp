/**
 * Copyright: Aimo_皑墨
 * Open Source Date: Jun 27, 2023
 * BiLiBiLi (哔哩哔哩) address: https://space.bilibili.com/146962867
 * Open source address(Git): https://github.com/AimoTvT/WidgetExpansions
 * We welcome the contributions of powerful movers and movers to join this plugin
 * Build powerful plugins together!!
 *
 * 版权所有权: Aimo_皑墨
 * 开源时间: 2023年6月27日
 * BiLiBiLi(哔哩哔哩)地址: https://space.bilibili.com/146962867
 * 开源地址(Git): https://github.com/AimoTvT/WidgetExpansions
 * 欢迎有实力的大佬/萌新加入本插件的贡献
 * 一起打造强大的插件!!!
 */


#include "SelectScrollBox/SelectScrollBox.h"
#include "IDButton/IDButton.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/ButtonSlot.h"
#include "Components/SizeBoxSlot.h"


void USelectScrollBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativeConstruct();
	}
}

//void USelectHorizontalBox::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
//{
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//	if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
//	{
//		TSharedPtr<SWidget> SafeWidget = GetCachedWidget();
//		if (SafeWidget.IsValid())
//		{
//			// Re-Run execute PreConstruct when we get a post edit property change, to do something
//			// akin to running Sync Properties, so users don't have to recompile to see updates.
//			NativePreConstruct();
//		}
//	}
//}

void USelectScrollBox::NativeConstruct()
{
	InitButton();
}


void USelectScrollBox::OnClickedID_Event(const FString& OnID)
{
	if (bRepeatedIndex || SelectIndex != IDs.Find(OnID))
	{
		OnClickedSelect.Broadcast(ID, OnID);
		SetSelectIndex(IDs.Find(OnID));
	}
}

void USelectScrollBox::OnHoveredID_Event(const FString& OnID)
{
	OnHoverSelect.Broadcast(ID, OnID);
}

void USelectScrollBox::SetSelectIndex(int Index, bool bDelegate)
{
	if (bDelegate && IDs.IsValidIndex(Index))
	{
		OnClickedSelect.Broadcast(ID, IDs[Index]);
	}
	if (Index != -1 && SelectIndex != Index)
	{
		if (SizeBoxWidgets.IsValidIndex(SelectIndex))
		{
			UIDButton* IDButton = Cast<UIDButton>(SizeBoxWidgets[SelectIndex]->GetChildAt(0));
			if (IDButton)
			{
				IDButton->SetStyle(DefaultStyle);
				UTextBlock* WidgetText = Cast<UTextBlock>(IDButton->GetChildAt(0));
				if (WidgetText)
				{
					WidgetText->SetColorAndOpacity(DefaultFontInfoColor);
				}
			}
		}
		if (SizeBoxWidgets.IsValidIndex(Index))
		{
			UIDButton* IDButton = Cast<UIDButton>(SizeBoxWidgets[Index]->GetChildAt(0));
			if (IDButton)
			{
				IDButton->SetStyle(SelectStyle);
				UTextBlock* WidgetText = Cast<UTextBlock>(IDButton->GetChildAt(0));
				if (WidgetText)
				{
					WidgetText->SetColorAndOpacity(SelectFontInfoColor);
				}
			}
		}
		SelectIndex = Index;
	}
}

void USelectScrollBox::InitButton()
{
	SelectIndex = 0;
	for (size_t i = 0; i < SizeBoxWidgets.Num(); i++)
	{
		SizeBoxWidgets[i]->RemoveFromParent();
	}
	SizeBoxWidgets.Empty();
	for (size_t i = 0; i < IDs.Num(); i++)
	{
		USizeBox* SizeBox = NewObject<USizeBox>(this);
		if (SizeBox == nullptr)
		{
			return;
		}
		SizeBoxWidgets.Add(SizeBox);
		UPanelSlot* PanelSlot = AddChild(SizeBox);
		if (PanelSlot)
		{
			UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(PanelSlot);
			if (ScrollBoxSlot)
			{
				ScrollBoxSlot->SetPadding(StylePadding);
			}
		}
		if (GetOrientation() == EOrientation::Orient_Vertical)
		{
			SizeBox->SetHeightOverride(ButttonSize);
		}
		else
		{
			SizeBox->SetMinDesiredWidth(ButttonSize);
		}
		UIDButton* IDButton = NewObject<UIDButton>(this);
		if (IDButton == nullptr)
		{
			return;
		}
		IDButton->ID = IDs[i];
		IDButton->OnClickedID.AddDynamic(this, &USelectScrollBox::OnClickedID_Event);
		IDButton->OnHoveredID.AddDynamic(this, &USelectScrollBox::OnHoveredID_Event);
		IDButton->SetStyle(SelectIndex == i ? SelectStyle : DefaultStyle);
		SizeBox->AddChild(IDButton);
		UTextBlock* WidgetText = NewObject<UTextBlock>(this);
		if (WidgetText)
		{
			WidgetText->SetColorAndOpacity(SelectIndex == i ? SelectFontInfoColor : DefaultFontInfoColor);
			if (SlateFontInfo.FontObject)
			{
				WidgetText->SetFont(SlateFontInfo);
			}
			if (Texts.IsValidIndex(i))
			{
				WidgetText->SetText(Texts[i]);
			}
			PanelSlot = IDButton->AddChild(WidgetText);
			if (PanelSlot)
			{
				UButtonSlot* ButtonSlot = Cast<UButtonSlot>(PanelSlot);
				if (ButtonSlot)
				{
					ButtonSlot->SetPadding(FontInfoPadding);
				}
			}
		}
	}
}

void USelectScrollBox::InitData(TArray<FString> InIDs, TArray<FText> InTexts)
{
	if (ReverseSelect)
	{
		IDs.Empty();
		int Index;
		for (size_t i = 0; i < InIDs.Num(); i++)
		{
			Index = InIDs.Num() - 1 - i;
			IDs.Add(InIDs[Index]);
			if (InTexts.IsValidIndex(Index))
			{
				Texts.Add(InTexts[Index]);
			}
			else
			{
				Texts.Add(FText());
			}
		}
	}
	else
	{
		IDs = InIDs;
		Texts = InTexts;
	}
	InitButton();
}

void USelectScrollBox::SetSelectID(const FString& OnID, bool bDelegate)
{
	if (bDelegate && IDs.Find(OnID) != -1)
	{
		OnClickedSelect.Broadcast(ID, OnID);
	}
	SetSelectIndex(IDs.Find(OnID));
}
