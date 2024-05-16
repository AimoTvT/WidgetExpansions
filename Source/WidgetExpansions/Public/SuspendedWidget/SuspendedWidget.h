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
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

#include "SuspendedWidget.generated.h"

/** *
 *
 */
UCLASS()
class WIDGETEXPANSIONS_API USuspendedWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** * 水平框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UHorizontalBox> HorizontalBoxWidget;

	/** * 尺寸框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<USizeBox> SizeBoxWidget;

	/** * 图像空间 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UImage> ImageWidget;

	/** * 文字控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UTextBlock> TextBlockWidget;



	/** * 三维位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector Location;

	/** * 三维位置终点位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector EndLocation;

	/** * 销毁时间 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float DestructTimer;

	/** * 动画速度 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float AnimTimer;

	/** * 视口偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector2D Offset;

	/** * 视口偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	bool bPlayerViewportRelative;


	/** * 定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FTimerHandle TimerHandle;

	/** * 销毁定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FTimerHandle DestructTimerHandle;


public:

	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	/** * 触发拖拽并传入控件 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetSuspended(const FString& String, const FVector& LocationT, const FVector& EndLocationT, TSoftObjectPtr<UObject> Image = nullptr, const FVector2D& ImageSize = FVector2D(50.0, 50.0));

	/** * 触发拖拽并传入控件,偏移版 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetSuspendedOffset(const FString& String, const FVector& LocationT, FVector OffsetLocationT = FVector(0.0f, 0.0f, 222.0f), TSoftObjectPtr<UObject> Image = nullptr, FVector2D ImageSize = FVector2D(50.0, 50.0));

	/** * 设置位置定时器 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void TimerHandleLocation();

	/** * 设置图像 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetImage(TSoftObjectPtr<UObject> Image, FVector2D ImageSize = FVector2D(50.0, 50.0));

	/** * 添加销毁时间 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void AddDestructTimer(float Timer);

	/** * 销毁定时器 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void NativeDestructTimerHandle();

	/** * 赛选动画 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SuspendedPlayAnimation(const FString& String);


};
