// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDrags/WidgetDragButton.h" /** * 拖拽按钮控件头文件 */
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h" /** * 控件函数头文件 */
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h" /** * 画布头文件 */



UWidgetDragButton::UWidgetDragButton()
{
	/** * 初始化数值 */
	DragWidget = nullptr;
	DragPositionOffset = { 0.0, 0.0 };
}

FString UWidgetDragButton::ICommunication_Implementation(UObject* InObject, const FString& InString, UObject*& InReturnObject)
{
	TArray<FString> Strings = UUniversalFunctionLibrarys::StringParseIntoArray(InString);
	UWidget* Widget = Cast<UWidget>(InObject);
	if (Widget && Strings.Num() >= 1 && Strings[0] == TEXT("OnDragWidget"))
	{
		if (Strings.Num() > 1 && Strings[1] != TEXT("0"))
		{
			OnDragWidget(Widget,true);
			return  TEXT("1");
		}
		else
		{
			OnDragWidget(Widget, false);
			return  TEXT("0");
		}
	}
	return  TEXT("0");
}

bool UWidgetDragButton::OnDragWidget(UWidget* Widget, bool bDrag)
{
	if (bDrag) /** * 是否拖拽 */
	{
		if (Widget) /** * 判断传入的控件是否存在 */
		{
			DragWidget = Widget; /** * 储存控件值 */
			TimerDragPosition();
			GetWorld()->GetTimerManager().SetTimer(DragTimerHandle, this, &UWidgetDragButton::TimerDragPosition, 0.001f, true); /** * 初始化设置定时器 */
			return true;
		}
		else
		{
			if (DragTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle); /** * 清除定时器 */
			}
			return false;
		}
	}
	else
	{
		Widget = nullptr; /** * 设置控件值 */
		if (DragTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle); /** * 清除定时器 */
		}
		return true;
	}
}

void UWidgetDragButton::TimerDragPosition()
{
	if (GetWorld() && DragWidget) /** * 世界和拖拽控件是否存在 */
	{
		FVector2D TDragPosition;
		TDragPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()); /** * 拖拽位置 = 获取鼠标的位置 */
		TDragPosition.X = TDragPosition.X * UWidgetLayoutLibrary::GetViewportScale(this); /** * 拖拽X位置*视口倍数 */
		TDragPosition.Y = TDragPosition.Y * UWidgetLayoutLibrary::GetViewportScale(this); /** * 拖拽Y位置*视口倍数 */
		UUserWidget* UserWidget = Cast<UUserWidget>(DragWidget); /** * 转换用户控件 */
		if (UserWidget && DragPosition != TDragPosition)
		{
			DragPosition = TDragPosition;
			UserWidget->SetPositionInViewport(TDragPosition); /** * 设置用户控件的位置 */
		}
		else
		{
			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DragWidget); /** * 转换为控件 */
			if (CanvasPanelSlot && DragPosition != TDragPosition)
			{
				DragPosition = TDragPosition;
				CanvasPanelSlot->SetPosition(TDragPosition); /** * 设置控件在位置 */
			}
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle); /** * 清除定时器 */
	}
}