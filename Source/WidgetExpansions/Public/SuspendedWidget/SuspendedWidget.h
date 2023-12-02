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

	/** 滚动条控件变量 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UHorizontalBox> HorizontalBoxWidget;

	/** 滚动条控件变量 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<USizeBox> SizeBoxWidget;

	/** 图像变量 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UImage> ImageWidget;

	/** 文字描述变量 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UTextBlock> TextBlockWidget;



	/** 三维位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector Location;

	/** 三维位置终点位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector EndLocation;

	/** 销毁时间 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float DestructTimer;

	/** 动画速度 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float AnimTimer;

	/** 视口偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector2D Offset;

	/** 视口偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	bool bPlayerViewportRelative;


	/** 定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FTimerHandle TimerHandle;

	/** 销毁定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FTimerHandle DestructTimerHandle;


public:

	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	/** 触发拖拽并传入控件 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetSuspended(const FString& String, const FVector& LocationT, const FVector& EndLocationT, TSoftObjectPtr<UObject> Image = nullptr, const FVector2D& ImageSize = FVector2D(50.0, 50.0));

	/** 触发拖拽并传入控件,偏移版 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetSuspendedOffset(const FString& String, const FVector& LocationT, FVector OffsetLocationT = FVector(0.0f, 0.0f, 222.0f), TSoftObjectPtr<UObject> Image = nullptr, FVector2D ImageSize = FVector2D(50.0, 50.0));

	/** 设置位置定时器 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void TimerHandleLocation();

	/** 设置图像 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetImage(TSoftObjectPtr<UObject> Image, FVector2D ImageSize = FVector2D(50.0, 50.0));

	/** 添加销毁时间 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void AddDestructTimer(float Timer);

	/** 销毁定时器 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void NativeDestructTimerHandle();

	/** 赛选动画 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SuspendedPlayAnimation(const FString& String);


};
