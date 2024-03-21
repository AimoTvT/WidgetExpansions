// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "PictureSequence.generated.h"

/** *
 *
 */
UCLASS()
class WIDGETEXPANSIONS_API UPictureSequence : public UUserWidget
{
	GENERATED_BODY()

public:

	/** * 图像控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "PictureSequence|Variable")
	TObjectPtr<UImage> ImageWidget;

	/** * 每秒帧数(切换图片的速度,越大越好) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	float FramesPerSecond = 25.0f;

	/** * 图片组的索引 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	int Texture2DsIndex = 0;

	/** * 图片组序列 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	TArray<TObjectPtr<UTexture2D>> Texture2Ds;

	/** * 切换图片的定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "PictureSequence|Variable")
	FTimerHandle FPSTimerHandle; 

	/** * 切换图片的定时器 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	bool bPictureEndRem = false; 


public:

	/** * 初始化控件 */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void InitWidget(TArray<UTexture2D*> OTexture2Ds, float OFramesPerSecond = 25.0f, int OTexture2DsIndex = 0);

	/** * 切换图片的定时器调用的函数 */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void OnFPSTimerHandle();

};
