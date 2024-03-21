// Fill out your copyright notice in the Description page of Project Settings.


#include "SizeBoxIDButton/SizeBoxIDButton.h"



void USizeBoxIDButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativeConstruct();
	}
}

//void USizeBoxIDButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
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

void USizeBoxIDButton::NativeConstruct()
{
	if (ButtonWidget == nullptr)
	{
		ButtonWidget = NewObject<UButton>(this);
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(this, "OnClickedID_Event"); //对接变量绑定函数
		ButtonWidget->OnClicked.AddUnique(ScriptDelegate); //对接变量绑定函数
		ScriptDelegate.BindUFunction(this, "OnHoveredID_Event"); //对接变量绑定函数
		ButtonWidget->OnHovered.AddUnique(ScriptDelegate); //对接变量绑定函数
		ButtonWidget->SetStyle(ButtonStyle);
		ClearChildren();
		AddChild(ButtonWidget);
	}
	
}

void USizeBoxIDButton::OnClickedID_Event()
{
	OnClickedID.Broadcast(ID);
}

void USizeBoxIDButton::OnHoveredID_Event()
{
	OnHoverID.Broadcast(ID);
}

void USizeBoxIDButton::SetID(const FString& InID)
{
	ID = InID;
}

void USizeBoxIDButton::SetButtonStyle(const FButtonStyle& InButtonStyle)
{
	ButtonStyle = InButtonStyle;
	if (ButtonWidget)
	{
		ButtonWidget->SetStyle(ButtonStyle);
	}
}

void USizeBoxIDButton::BindScriptDelegate(UObject* InObject, const FName& InFunctionName, bool bClicked)
{
	if (InObject)
	{
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(InObject, InFunctionName); //对接变量绑定函数
		if (bClicked)
		{
			OnClickedID.Add(ScriptDelegate);
		}
		else
		{
			OnHoverID.Add(ScriptDelegate);
		}
	}
}
