// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h" /** 按钮控件 */
#include "UniversalInterface/Public/UniversalInterfaces.h"
#include "UniversalFunctionLibrary/Public/UniversalFunctionLibrarys.h"


#include "WidgetDragButton.generated.h"


/**
 *
 */
UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "WidgetDragButton")) /** 设置在用户控件编辑器里显示的名字 */
class WIDGETEXPANSIONS_API UWidgetDragButton : public UButton, public IUniversalInterfaces
{
	GENERATED_BODY()

	UWidgetDragButton();

public:

	/** 拖拽的控件 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		UWidget* DragWidget;

	/** 拖拽的位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		FVector2D DragPosition;

	/** 拖拽的位置偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		FVector2D DragPositionOffset;

	/** 拖拽的定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		FTimerHandle DragTimerHandle;

protected:

	virtual FString ICommunication_Implementation(UObject* Object, const FString& String, UObject*& ReturnObject);

public:



	/** 触发拖拽并传入控件 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		bool OnDragWidget(UWidget* Widget,bool bDrag);

	/** 定时器调用的事件,修改控件的位置 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		void TimerDragPosition();

};
