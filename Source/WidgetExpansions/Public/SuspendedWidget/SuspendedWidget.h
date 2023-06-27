// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/SizeBox.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/HorizontalBox.h"

#include "SuspendedWidget.generated.h"

/**
 *
 */
UCLASS()
class WIDGETEXPANSIONS_API USuspendedWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
		/** 滚动条控件变量 */
		UHorizontalBox* HorizontalBoxWidget;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
		/** 滚动条控件变量 */
		USizeBox* SizeBoxWidget;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
		/** 图像变量 */
		UImage* ImageWidget;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
		/** 文字描述变量 */
		UTextBlock* TextBlockWidget;



	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 三维位置 */
		FVector Location;

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 三维位置终点位置 */
		FVector EndLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 销毁时间 */
		float DestructTimer;

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 动画速度 */
		float AnimTimer;

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 视口偏移 */
		FVector2D Offset;

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 视口偏移 */
		bool bPlayerViewportRelative;


	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 定时器 */
		FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 销毁定时器 */
		FTimerHandle DestructTimerHandle;


public:

	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 触发拖拽并传入控件 */
		virtual void SetSuspended(const FString& String, const FVector& LocationT, const FVector& EndLocationT, TSoftObjectPtr<UObject> Image = nullptr, const FVector2D& ImageSize = FVector2D(50.0, 50.0));

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 触发拖拽并传入控件,偏移版 */
		virtual void SetSuspendedOffset(const FString& String, const FVector& LocationT, FVector OffsetLocationT = FVector(0.0f, 0.0f, 222.0f), TSoftObjectPtr<UObject> Image = nullptr, FVector2D ImageSize = FVector2D(50.0,50.0));

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 设置位置定时器 */
		virtual void TimerHandleLocation();

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 设置图像 */
		virtual void SetImage(TSoftObjectPtr<UObject> Image, FVector2D ImageSize = FVector2D(50.0, 50.0));

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 添加销毁时间 */
		virtual void AddDestructTimer(float Timer);

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 销毁定时器 */
		virtual void NativeDestructTimerHandle();

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 赛选动画 */
		virtual void SuspendedPlayAnimation(const FString& String);

	
};
