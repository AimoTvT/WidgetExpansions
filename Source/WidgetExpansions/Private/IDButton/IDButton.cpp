// Fill out your copyright notice in the Description page of Project Settings.


#include "IDButton/IDButton.h"


void UIDButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt(); 
	if (IsDesignTime() == false)
	{
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(this, "OnIDClicked_Event"); //对接变量绑定函数
		OnClicked.AddUnique(ScriptDelegate);
		ScriptDelegate.BindUFunction(this, "OnIDHovered_Event"); //对接变量绑定函数
		OnHovered.AddUnique(ScriptDelegate);
	}
	return;
}
void UIDButton::OnIDClicked_Event()
{
	OnIDClicked.Broadcast(ID);
}

void UIDButton::OnIDHovered_Event()
{
	OnIDHovered.Broadcast(ID);
}


