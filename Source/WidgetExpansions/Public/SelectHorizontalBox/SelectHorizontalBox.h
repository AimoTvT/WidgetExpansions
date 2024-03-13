// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "SelectHorizontalBox.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API USelectHorizontalBox : public UHorizontalBox
{
	GENERATED_BODY()

public:

	/** 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	FString ID;

	/** 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable") 
	TArray<FString> IDs;

	/** 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	TArray<FText> Texts;

	/** 选择索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	int SelectIndex;

	/** 默认样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle DefaultStyle;

	/** 选择样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle SelectStyle;

	/** 文字样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FSlateFontInfo SlateFontInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	/** 资源图片组 */
	TArray<TObjectPtr<UButton>> ButtonWidgets;

	/** * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIDClickedEvent, const FString&, OnID, const FString&, SelectID);

	/** * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIDHoverEvent, const FString&, OnID, const FString&, SelectID);

	/** * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SelectHorizontalBox|On")
		FOnIDClickedEvent OnClickedSelect;

	/** * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SelectHorizontalBox|On")
		FOnIDHoverEvent OnHoverSelect;

protected:
	/** Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativePreConstruct();

public:

	/* * 按下的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void OnIDClicked_Event(const FString& OnID);

	/* * 触摸的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void OnIDHovered_Event(const FString& OnID);

	/* * 设置索引显示,是否委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void SetSelectIndex(int Index, bool bDelegate = false);

	/* * 初始化按钮 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void InitButton();

	/* * 初始化数据 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void InitData(TArray<FString> InIDs, TArray<FText> InTexts);

	/* * 设置选择ID */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void SetSelectID(const FString& OnID, bool bDelegate = false);

};
