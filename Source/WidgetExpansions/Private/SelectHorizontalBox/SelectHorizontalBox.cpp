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


#include "SelectHorizontalBox/SelectHorizontalBox.h"
#include "IDButton/IDButton.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"


void USelectHorizontalBox::OnWidgetRebuilt()
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

void USelectHorizontalBox::NativeConstruct()
{
	InitButton();
}


void USelectHorizontalBox::OnClickedID_Event(const FString& OnID)
{
	OnClickedSelect.Broadcast(ID, OnID);
	SetSelectIndex(IDs.Find(OnID));
}

void USelectHorizontalBox::OnHoveredID_Event(const FString& OnID)
{
	OnHoverSelect.Broadcast(ID, OnID);
}

void USelectHorizontalBox::SetSelectIndex(int Index, bool bDelegate)
{
	if (bDelegate && IDs.IsValidIndex(Index))
	{
		OnClickedSelect.Broadcast(ID, IDs[Index]);
	}
	if (Index != -1 && SelectIndex != Index)
	{
		if (ButtonWidgets.IsValidIndex(SelectIndex))
		{
			ButtonWidgets[SelectIndex]->SetStyle(DefaultStyle);
		}
		if (ButtonWidgets.IsValidIndex(Index))
		{
			ButtonWidgets[Index]->SetStyle(SelectStyle);
		}
		SelectIndex = Index;
	}
}

void USelectHorizontalBox::InitButton()
{
	for (size_t i = 0; i < ButtonWidgets.Num(); i++)
	{
		ButtonWidgets[i]->RemoveFromParent();
	}
	ButtonWidgets.Empty();
	for (size_t i = 0; i < IDs.Num(); i++)
	{
		UIDButton* IDButton = NewObject<UIDButton>(this);
		if (IDButton)
		{
			ButtonWidgets.Add(IDButton);
			IDButton->ID = IDs[i];
			FScriptDelegate ScriptDelegate; //建立对接变量
			ScriptDelegate.BindUFunction(this, TEXT("OnClickedID_Event")); //对接变量绑定函数
			IDButton->OnClickedID.AddUnique(ScriptDelegate); //对接变量绑定函数
			ScriptDelegate.BindUFunction(this, TEXT("OnHoveredID_Event")); //对接变量绑定函数
			IDButton->OnHoveredID.AddUnique(ScriptDelegate); //对接变量绑定函数
			IDButton->SetStyle(SelectIndex == i ? SelectStyle : DefaultStyle);
			UPanelSlot* PanelSlot = AddChild(IDButton);
			if (PanelSlot)
			{
				UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(PanelSlot);
				if (HorizontalBoxSlot)
				{
					FSlateChildSize InSize;
					InSize.SizeRule = ESlateSizeRule::Fill;
					HorizontalBoxSlot->SetSize(InSize);
				}
			}
			UTextBlock* WidgetText = NewObject<UTextBlock>(this);
			if (WidgetText)
			{
				if (SlateFontInfo.FontObject)
				{
					WidgetText->SetFont(SlateFontInfo);
				}
				if (Texts.IsValidIndex(i))
				{
					WidgetText->SetText(Texts[i]);
				}
				IDButton->AddChild(WidgetText);
			}
		}
	}
}

void USelectHorizontalBox::InitData(TArray<FString> InIDs, TArray<FText> InTexts)
{
	IDs = InIDs;
	Texts = InTexts;
	InitButton();
}

void USelectHorizontalBox::SetSelectID(const FString& OnID, bool bDelegate)
{
	if (bDelegate && IDs.Find(OnID) != -1)
	{
		OnClickedSelect.Broadcast(ID, OnID);
	}
	SetSelectIndex(IDs.Find(OnID));
}
