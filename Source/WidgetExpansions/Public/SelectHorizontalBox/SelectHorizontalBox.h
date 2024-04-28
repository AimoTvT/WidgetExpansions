// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "SelectHorizontalBox.generated.h"

/** *
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API USelectHorizontalBox : public UHorizontalBox
{
	GENERATED_BODY()

public:

	/** * 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	FString ID;

	/** * ID组 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable") 
	TArray<FString> IDs;

	/** * 文字组 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	TArray<FText> Texts;

	/** * 选择索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	int SelectIndex;

	/** * 默认样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle DefaultStyle;

	/** * 选择样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle SelectStyle;

	/** * 文字样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FSlateFontInfo SlateFontInfo;

	/** * 按钮控件组 */
	UPROPERTY(BlueprintReadWrite, Category = "SelectHorizontalBox|Variable")
	TArray<TObjectPtr<UButton>> ButtonWidgets;

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClickedIDEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHoverIDEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 点击选着 */
	UPROPERTY(BlueprintAssignable, Category = "SelectHorizontalBox|On")
	FOnClickedIDEvent OnClickedSelect;

	/** * * 悬浮选择 */
	UPROPERTY(BlueprintAssignable, Category = "SelectHorizontalBox|On")
	FOnHoverIDEvent OnHoverSelect;

protected:
	/** * Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativeConstruct();

public:

	/* * 点击的委托_事件 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void OnClickedID_Event(const FString& OnID);

	/* * 悬浮的委托_事件 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void OnHoveredID_Event(const FString& OnID);

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
