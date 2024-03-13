// Fill out your copyright notice in the Description page of Project Settings.


#include "SizeBoxIDButton/SizeBoxIDButton.h"

void USizeBoxIDButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativePreConstruct();
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

void USizeBoxIDButton::NativePreConstruct()
{
	if (Button == nullptr)
	{
		Button = NewObject<UButton>(this);
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(this, "OnIDClicked_Event"); //对接变量绑定函数
		Button->OnClicked.AddUnique(ScriptDelegate); //对接变量绑定函数
		ScriptDelegate.BindUFunction(this, "OnIDHovered_Event"); //对接变量绑定函数
		Button->OnHovered.AddUnique(ScriptDelegate); //对接变量绑定函数
		ClearChildren();
		AddChild(Button);
	}
	
}

void USizeBoxIDButton::OnIDClicked_Event()
{
	OnIDClicked.Broadcast(ID);
}

void USizeBoxIDButton::OnIDHovered_Event()
{
	OnIDHover.Broadcast(ID);
}