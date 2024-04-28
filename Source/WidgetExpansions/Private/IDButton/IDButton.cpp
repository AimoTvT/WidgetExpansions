// Fill out your copyright notice in the Description page of Project Settings.


#include "IDButton/IDButton.h"


void UIDButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt(); 
	if (IsDesignTime() == false)
	{
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(this, TEXT("OnClickedID_Event")); //对接变量绑定函数
		OnClicked.AddUnique(ScriptDelegate);
		ScriptDelegate.BindUFunction(this, TEXT("OnHoveredID_Event")); //对接变量绑定函数
		OnHovered.AddUnique(ScriptDelegate);
	}
	return;
}
void UIDButton::OnClickedID_Event()
{
	OnClickedID.Broadcast(ID);
}

void UIDButton::OnHoveredID_Event()
{
	OnHoveredID.Broadcast(ID);
}


