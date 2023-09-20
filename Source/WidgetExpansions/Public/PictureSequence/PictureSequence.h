// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "PictureSequence.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UPictureSequence : public UUserWidget
{
	GENERATED_BODY()

public:

	/** 图像变量 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
		UImage* ImageWidget = nullptr;

	/** 每秒帧数(切换图片的速度,越大越好) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		float FramesPerSecond = 25.0f;

	/** 图片组的索引 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		int Texture2DsIndex = 0;

	/** 图片组序列 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		TArray<UTexture2D*> Texture2Ds = {};

	/** 切换图片的定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		FTimerHandle FPSTimerHandle; //定义变量.h

	/** 切换图片的定时器 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		bool bPictureEndRem = false; //定义变量.h


public:

	/** 初始化 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		virtual void InitWidget(TArray<UTexture2D*> OTexture2Ds, float OFramesPerSecond = 25.0f, int OTexture2DsIndex = 0);

	/** 切换图片的定时器调用的函数 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		virtual void OnFPSTimerHandle();
	
};
