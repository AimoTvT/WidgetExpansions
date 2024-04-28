// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectScrollBox/SelectScrollBox.h"
#include "IDButton/IDButton.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"


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
	OnClickedSelect.Broadcast(ID, OnID);
	SetSelectIndex(IDs.Find(OnID));
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
			}
		}
		if (SizeBoxWidgets.IsValidIndex(Index))
		{
			UIDButton* IDButton = Cast<UIDButton>(SizeBoxWidgets[Index]->GetChildAt(0));
			if (IDButton)
			{
				IDButton->SetStyle(SelectStyle);
			}
		}
		SelectIndex = Index;
	}
}

void USelectScrollBox::InitButton()
{
	for (size_t i = 0; i < SizeBoxWidgets.Num(); i++)
	{
		SizeBoxWidgets[i]->RemoveFromParent();
	}
	for (size_t i = 0; i < IDs.Num(); i++)
	{
		USizeBox* SizeBox = NewObject<USizeBox>(this);
		if (SizeBox == nullptr)
		{
			return;
		}
		SizeBoxWidgets.Add(SizeBox);
		AddChild(SizeBox);
		if (GetOrientation() == EOrientation::Orient_Vertical)
		{
			SizeBox->SetHeightOverride(ButttonSize);
		}
		else
		{
			if (ButttonSize > 0.0f)
			{
				SizeBox->SetWidthOverride(ButttonSize);
			}
		}
		UIDButton* IDButton = NewObject<UIDButton>(this);
		if (IDButton == nullptr)
		{
			return;
		}
		IDButton->ID = IDs[i];
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(this, TEXT("OnClickedID_Event")); //对接变量绑定函数
		IDButton->OnClickedID.AddUnique(ScriptDelegate); //对接变量绑定函数
		ScriptDelegate.BindUFunction(this, TEXT("OnHoveredID_Event")); //对接变量绑定函数
		IDButton->OnHoveredID.AddUnique(ScriptDelegate); //对接变量绑定函数
		IDButton->SetStyle(SelectIndex == i ? SelectStyle : DefaultStyle);
		UPanelSlot* PanelSlot = SizeBox->AddChild(IDButton);
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

void USelectScrollBox::InitData(TArray<FString> InIDs, TArray<FText> InTexts)
{
	IDs = InIDs;
	Texts = InTexts;
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
