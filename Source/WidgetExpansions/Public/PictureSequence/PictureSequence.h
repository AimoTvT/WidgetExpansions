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

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
		/** 图像变量 */
		UImage* ImageWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		/** 每秒帧数(切换图片的速度,越大越好) */
		float FramesPerSecond = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		/** 图片组的索引 */
		int Texture2DsIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		/** 图片组序列 */
		TArray<UTexture2D*> Texture2Ds = {};

	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
		/** 切换图片的定时器 */
		FTimerHandle FPSTimerHandle; //定义变量.h


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
		/** 切换图片的定时器 */
		bool bPictureEndRem = false; //定义变量.h


public:

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 初始化 */
		virtual void InitWidget(TArray<UTexture2D*> OTexture2Ds, float OFramesPerSecond = 25.0f, int OTexture2DsIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
		/** 切换图片的定时器调用的函数 */
		virtual void OnFPSTimerHandle();
	
};
